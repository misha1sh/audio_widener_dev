#pragma once

#include "kfr/all.hpp"

#include "ProcessingParams.h"

class MainProcessor {
public:
    explicit MainProcessor(ProcessingParams* params);

    void process(kfr::univector<kfr::univector<kfr::f32, 0>, 2> data);
    int getLatencyInSamples();

private:
    ProcessingParams& params;
};
