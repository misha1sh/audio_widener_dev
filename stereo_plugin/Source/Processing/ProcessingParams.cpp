#include "ProcessingParams.h"

#include <memory>

ProcessingParams::ProcessingParams(AudioProcessor& processor) {
    processor.addParameter(leftCutoff=new AudioParameterFloat("leftCutoff", // parameterID
                                                              "leftCutoff", // parameter name
                                                              0.0f,   // minimum value
                                                              3.0f,   // maximum value
                                                              0.5f));
    processor.addParameter(rightCutoff=new AudioParameterFloat("rightCutoff", // parameterID
                                                              "rightCutoff", // parameter name
                                                              0.0f,   // minimum value
                                                              3.0f,   // maximum value
                                                              0.5f));
}

