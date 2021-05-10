#pragma once

#include "kfr/all.hpp"

#include "ProcessingParams.h"
#include "DataAccumulator.h"

#define FFT_SZ 2048
#define FFT_RES_SZ (FFT_SZ / 2 + 1)
#define OVERLAP_COUNT 0

class MainProcessor {
public:
    explicit MainProcessor(ProcessingParams& params);

    void reset();

    void process(kfr::univector<kfr::univector<kfr::f32, 0>, 2> data);
    int getLatencyInSamples();

private:
    ProcessingParams& params;
    DataAccumulator inAccumulators[2];
    DataAccumulator outAccumulators[2];

    kfr::dft_plan_real<kfr::f32> dftPlan;
    kfr::univector<kfr::u8> dftPlanTemp;
    kfr::univector<kfr::f32> dftWindow;



    void processFFTForAccumulator(DataAccumulator& inAccumulator, DataAccumulator& outAccumulator1,
                                  DataAccumulator& outAccumulator2);
    void performIFFTAndWrite(kfr::univector<kfr::complex<kfr::f32>, FFT_RES_SZ>& in, DataAccumulator& outAccumulator);
    void applyConversionsToFFT(kfr::univector<kfr::complex<kfr::f32>, FFT_RES_SZ>& fftData);
    void processSplit(kfr::univector<kfr::complex<kfr::f32>, 0> data);
    void generateMask(kfr::univector<kfr::complex<kfr::f32>, 0> data,
                      kfr::univector<kfr::f32, 0> mask);
    int freqToFFTIndex(int frequency) const;
};
