#pragma once

#include <JuceHeader.h>



namespace DynamicTextureOpenGL
{

	struct Vertex
	{
		GLfloat position[2];
	};

	class Attributes
	{
	public:
		std::unique_ptr<juce::OpenGLShaderProgram::Attribute> position;
		Attributes(juce::OpenGLContext& context, juce::OpenGLShaderProgram& shader);

		void enable(juce::OpenGLContext& context);
		void disable(juce::OpenGLContext& context);

	private:
		static juce::OpenGLShaderProgram::Attribute* createAttribute(juce::OpenGLContext& context,
			juce::OpenGLShaderProgram& shader,
			const juce::String& attributeName);
		

	};
}

