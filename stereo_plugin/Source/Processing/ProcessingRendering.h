#pragma once

#include "SyncedArray.h"

class ProcessingRendering {
public:
    Atomic<float> lastSampleRate;
    Atomic<float> lastMaskDiff;

    SyncedArray<float> lastMask;
    SyncedArray<float> lastSound;

    ProcessingRendering() : lastSampleRate(), lastMaskDiff(),
                            lastMask(0.9f), lastSound(0.97f) {

    }
};
