#pragma once

class ProcessingRendering {
public:
    Atomic<float> lastSampleRate;
    Atomic<float> lastMaskDiff;
};
