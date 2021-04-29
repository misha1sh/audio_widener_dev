#pragma once

#include "JuceHeader.h"



namespace DynamicTextureOpenGL
{
    class Uniforms
    {
    public:
        Uniforms(juce::OpenGLContext& context, juce::OpenGLShaderProgram& shader);
        void enable(juce::OpenGLContext& context);
        void disable(juce::OpenGLContext& context);

        std::unique_ptr<juce::OpenGLShaderProgram::Uniform> offsetX;
    private:

        static juce::OpenGLShaderProgram::Uniform* createUniform(juce::OpenGLContext& context,
            juce::OpenGLShaderProgram& shaderProgram,
            const juce::String& uniformName);
    };
}