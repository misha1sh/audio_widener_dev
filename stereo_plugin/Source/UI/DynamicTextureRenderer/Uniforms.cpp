#include "Uniforms.h"

using namespace DynamicTextureOpenGL;

Uniforms::Uniforms(juce::OpenGLContext& context, juce::OpenGLShaderProgram& shader)
{
	offsetX.reset(createUniform(context, shader, "offsetX"));
}


juce::OpenGLShaderProgram::Uniform* Uniforms::createUniform(juce::OpenGLContext& context,
                                                            juce::OpenGLShaderProgram& shaderProgram, const juce::String& uniformName)
{
	if (context.extensions.glGetUniformLocation(shaderProgram.getProgramID(), uniformName.toRawUTF8()) < 0)
	{
		DBG("Unable to find uniform " + uniformName + " in spectrum shader");
		jassertfalse;
	}

	return new juce::OpenGLShaderProgram::Uniform(shaderProgram, uniformName.toRawUTF8());
}

