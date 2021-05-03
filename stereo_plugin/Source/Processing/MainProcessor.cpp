#include "MainProcessor.h"

using namespace kfr;

void MainProcessor::process(kfr::univector<kfr::univector<kfr::f32, 0>, 2> data) {

    univector<f32, 127> taps127;
    expression_pointer<f32> kaiser = to_pointer(window_kaiser(taps127.size(), 3.0, ctype_t<f32>()));

    float leftCutoff = *params->leftCutoff;
    float rightCutofff = *params->rightCutoff;
// Fill taps127 with the band pass FIR filter coefficients using kaiser window and cutoff=0.2 and 0.4
    fir_bandpass(taps127, params->, 0.4, kaiser, true);
    filter_fir<f32> filter(taps127);
    filter.apply(data[0]);

    fir_bandstop(taps127, 0.2, 0.4, kaiser, true);
    filter_fir<f32> filter2(taps127);
    filter2.apply(data[1]);
}

int MainProcessor::getLatencyInSamples() {
    return 10;
}

MainProcessor::MainProcessor(ProcessingParams& _params): params(_params) {

}

