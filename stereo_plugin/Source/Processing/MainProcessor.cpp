#include "MainProcessor.h"

using namespace kfr;

MainProcessor::MainProcessor(ProcessingParams& _params):
    params(_params),
    dftPlan(FFT_SZ),
    dftPlanTemp(dftPlan.temp_size),
    dftWindow(window_hann(FFT_SZ)) {
}


void MainProcessor::reset() {
    univector<f32> zeros(getLatencyInSamples(), 0);

    for (int i = 0; i < 2; i++) {
        inAccumulators[i].reset(params.maxSamplesPerBlock, FFT_SZ);
        inAccumulators[i].addDataSamples(zeros);
        outAccumulators[i].reset(params.maxSamplesPerBlock, FFT_SZ);
    }
}

void MainProcessor::process(univector<univector<f32, 0>, 2> data) {
    for (int i = 0; i < 2; i++) {
        inAccumulators[i].addDataSamples(data[i]);
    }

    for (int i = 0; i < 2; i++) {
        processFFTForAccumulator(inAccumulators[i], outAccumulators[i]);
    }
    static int iterCount = 0;
    iterCount++;
    for (int i = 0; i < 2; i++) {
        // overlap-add
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

        applyConversionsToFFT(fftOut);


    }
}


void MainProcessor::performIFFTAndWrite(univector<complex<f32>, FFT_RES_SZ>& in, DataAccumulator& outAccumulator) {
    static univector<f32, FFT_SZ> ifftResult;
    dftPlan.execute(ifftResult, in , dftPlanTemp); // inverse
    ifftResult /= FFT_SZ;

    outAccumulator.addDataSamples(ifftResult);
}


inline complex<f32> convertToCartesian(const complex<f32>& a) {
    auto x = std::polar(a.real(), a.imag());
    return {x.real(), x.imag()};
}

#define magintudes(x) real(x)
#define phases(x) imag(x)
#define magnitude(x) x.real()
#define phase(x) x.imag()


void MainProcessor::applyConversionsToFFT(univector<complex<f32>, FFT_RES_SZ>& fftData) {
    fftData = kfr::polar(fftData);

    int leftFreq = freqToFFTIndex(*params.leftCutoff);
    int rightFreq = freqToFFTIndex(*params.rightCutoff);

    auto dataToProcess = fftData.slice(leftFreq, rightFreq);

    for (size_t i = 0; i < fftData.size(); i++) {
        fftData[i] = convertToCartesian(fftData[i]);
    }
}

void MainProcessor::processSplit(univector<complex<f32>, 0> data) {
    static univector<f32, FFT_RES_SZ> mask;
    generateMask(data, mask);

    for (int i = 0; i < data.size(); i++) {
        data[]
    }
}

void MainProcessor::generateMask(univector<complex<f32>, 0> data,
                                 univector<f32, 0> mask) {
    //f32 magSum = sum(magintudes(data));
    float sineX = 0.f;
    for (int i = 0; i < data.size(); i++) {
        sineX += magnitude(data[i]) * *params.sineStretch;
        float sineY = sin(sineX);
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


