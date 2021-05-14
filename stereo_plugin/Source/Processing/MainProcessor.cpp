#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
#include "MainProcessor.h"

using namespace kfr;

MainProcessor::MainProcessor(ProcessingParams& _params, ProcessingRendering& _rendering):
    params(_params),
    rendering(_rendering),
    dftPlan(FFT_SZ),
    dftPlanTemp(dftPlan.temp_size),
    dftWindow(window_hann(FFT_SZ)) {
}


void MainProcessor::reset() {
    univector<f32> zeros(getLatencyInSamples(), 0);
    int ovCont = OVERLAP_COUNT;
    univector<f32> overlapZeros(OVERLAP_COUNT, 0);

    inSumAccumulator.reset(params.maxSamplesPerBlock, FFT_SZ);
    inSumAccumulator.addDataSamples(zeros);
    for (int i = 0; i < 2; i++) {
        inAccumulators[i].reset(params.maxSamplesPerBlock, FFT_SZ);
        inAccumulators[i].addDataSamples(zeros);
        outAccumulators[i].reset(params.maxSamplesPerBlock, FFT_SZ);
        fftOutAccumulators[i].reset(params.maxSamplesPerBlock, FFT_SZ);
        fftOutAccumulators[i].addDataSamples(overlapZeros);
    }
}

void MainProcessor::process(univector<univector<f32, 0>, 2> data) {
   /* for (int i = 0; i < 2; i++) {
        inAccumulators[i].addDataSamples(data[i]);
    }*/
    static int iterCount = 0;
    iterCount++;

    data[0] += data[1];
    data[0] /= 2;
    inSumAccumulator.addDataSamples(data[0]);

    processFFTForAccumulator(inSumAccumulator, fftOutAccumulators[0], fftOutAccumulators[1]);

    static univector<f32, FFT_SZ / 2> overlapAddBuffer;
    for (int i = 0; i < 2; i++) {
        // overlap-add
        while (fftOutAccumulators[i].size() >= 2 * OVERLAP_COUNT) {
            univector_ref<f32> leftSegment(fftOutAccumulators[i].getData(OVERLAP_COUNT, 0));
            univector_ref<f32> mediumSegment(fftOutAccumulators[i].getData(OVERLAP_COUNT,0));

            std::fill(overlapAddBuffer.begin(), overlapAddBuffer.end(), 0);
            overlapAddBuffer += leftSegment;
            overlapAddBuffer += mediumSegment;
            overlapAddBuffer /= 2.f;

            outAccumulators[i].addDataSamples(overlapAddBuffer);
        }


        jassert(fftOutAccumulators[i].size() == OVERLAP_COUNT);

    }

    for (int i = 0; i < 2; i++) {
        univector_ref<f32> res(outAccumulators[i].getData(data[i].size(), 0));
        builtin_memcpy(&data[i][0], &res[0], data[i].size() * sizeof(f32));
    }
}

void MainProcessor::processFFTForAccumulator(DataAccumulator& inAccumulator,
                                             DataAccumulator& outAccumulator1,
                                             DataAccumulator& outAccumulator2) {
    while (inAccumulator.size() >= FFT_SZ) {
        univector_ref<f32> in = inAccumulator.getData(FFT_SZ - OVERLAP_COUNT, OVERLAP_COUNT);

        static univector<complex<f32>, FFT_RES_SZ> fftOut;
        dftPlan.execute(fftOut, in, dftPlanTemp); // direct; returns FFT_SZ / 2 + 1 array

        static univector<complex<f32>, FFT_RES_SZ> fftOut1, fftOut2;
        applyConversionsToFFT(fftOut, fftOut1, fftOut2);

        performIFFTAndWrite(fftOut1, outAccumulator1);
        performIFFTAndWrite(fftOut2, outAccumulator2);
    }
}


void MainProcessor::performIFFTAndWrite(vecfft& in, DataAccumulator& outAccumulator) {
    static univector<f32, FFT_SZ> ifftResult;
    dftPlan.execute(ifftResult, in , dftPlanTemp); // inverse
    ifftResult *= dftWindow;
    ifftResult /= FFT_SZ;

    outAccumulator.addDataSamples(ifftResult);
}


inline complex<f32> convertToCartesian(const complex<f32>& a) {
    auto x = std::polar(a.real(), a.imag());
    return {x.real(), x.imag()};
}

#define magnitudes(x) real(x)
#define phases(x) imag(x)
#define magnitude(x) x.real()
#define phase(x) x.imag()


void MainProcessor::applyConversionsToFFT(vecfft& fftData, vecfft& res1, vecfft& res2) {
    /*res1 = fftData;
    res2 = fftData;
    return;*/
    /*   fill(fftData.begin(), fftData.end(), 0);

   /*


       for (int i = 320; i < 430; i++) {
           fftData[freqToFFTIndex(i)] = {10, 10};
       }
       res1 = fftData;
       res2 = fftData;*/


/*    static univector<complex<f32>, FFT_RES_SZ> oldRes;
    float diff = 0;
    for (int i = 0; i < fftData.size(); i++) {
        diff += fabs(cabs(oldRes[i]) - cabs(fftData[i]));
        oldRes[i] = fftData[i];
    }
    rendering.lastMaskDiff = diff * 0.05f +  0.95f * rendering.lastMaskDiff.get();

    res1 = fftData;
    res2 = fftData;
    static univector<f32, FFT_RES_SZ> mask;// = window_hann(FFT_RES_SZ) * 2;

    for (int i = 0; i < min(mask.size(), 50); i++) {
        mask[i] = 0;
    }
    for (int j = 50; j < mask.size(); j++) {
        mask[j] = 2;
    }

    for (int i = 0; i < min(fftData.size(), 100);res1.size() i++) {
      /*  if (cabs(fftData[i]) < 0.1) {
            continue;
        }*/
  /*     res1[i] = {res1[i].real() * mask[i], res1[i].imag() * mask[i]};
        res2[i] = {res2[i].real() * (2 - mask[i]), res2[i].imag() * (2 - mask[i])};
    }*/

    fftData = kfr::polar(fftData);
    res1 = fftData;
    res2 = fftData;

    processSplit(fftData, res1, res2);

    int leftFreq = freqToFFTIndex(*params.leftCutoff);
    int rightFreq = freqToFFTIndex(*params.rightCutoff);

    for (size_t i = 0; i < leftFreq; i++) {
        res1[i] = res2[i] = convertToCartesian(fftData[i]);
    }

    for (size_t i = leftFreq; i < rightFreq; i++) {
        res1[i] = convertToCartesian(res1[i]);
        res2[i] = convertToCartesian(res2[i]);
    }

    for (size_t i = rightFreq; i < fftData.size(); i++) {
        res1[i] = res2[i] = convertToCartesian(fftData[i]);
    }


}

void MainProcessor::processSplit(vecfft& data, vecfft& res1, vecfft& res2) {
    static univector<f32, FFT_RES_SZ> mask;
    generateMask(data, mask);

    mask += 1;

    static univector<f32, FFT_RES_SZ> oldMask;
    float diff = 0;
    for (int i = 0; i < data.size(); i++) {
        diff += fabs(oldMask[i] - mask[i]);
        oldMask[i] = mask[i];
    }
    rendering.lastMaskDiff = diff ;

  /*  for (int i = 0; i < mask.size(); i++) {
        mask[i] = sin(i / 512.f) + 1;
        //mask[i] = 1.0;
    }
    mask = window_hann(mask.size()) * 2;*/
    for (int i = 0; i < data.size(); i++) {
        res1[i] = {magnitude(data[i]) * mask[i], phase(data[i])};
        res2[i] = {magnitude(data[i]) * (2 - mask[i]), phase(data[i])};
    }
}

// mask [-1, 1]
void MainProcessor::generateMask(vecfft& data, univector<f32, 0> mask) {
    //f32 magSum = sum(magintudes(data));
    static univector<f32, FFT_RES_SZ> mediumMagnitude(0);
    float weight = *params.attack;
    float otherWeight = 1 - weight;
   for (int i = 0; i < data.size(); i++) {
        mediumMagnitude[i] = weight * mediumMagnitude[i] + otherWeight * magnitude(data[i]);
    }
  /* if (weight < 0.5) {
       for (int i = 0; i < data.size(); i++) {
           mediumMagnitude[i] = magnitude(data[i]);
       }
   }*/

    float sineX = 0.f;
    float sineStretch = *params.sineStretch;
    for (int i = 0; i < data.size(); i++) {
        sineX += mediumMagnitude[i] / sineStretch / 100;
        float sineY = cos(sineX);
        mask[i] = sineY;
    }
}

//           N:  0, 1, 2,   3    ..  FFT_RES_SZ - 1
// frequencies:  0, x, 2*x  3*x  ..  sample_rate / 2 (Nyquist frequency)
int MainProcessor::freqToFFTIndex(int frequency) const {
    return (int)((float)frequency / params.sampleRate * 2 * (FFT_RES_SZ - 1));
}

int MainProcessor::getLatencyInSamples() {
    return FFT_SZ;
}



#pragma clang diagnostic pop