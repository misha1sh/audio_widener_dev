#pragma once

#include <JuceHeader.h>

#include "Attributes.h"
#include "Texture.h"
#include "VertexBuffer.h"

namespace SpectrumOpenGL
{


	struct Uniforms
	{
		Uniforms(juce::OpenGLContext& context, juce::OpenGLShaderProgram& shader);
	};

	class SpectrumRenderer : private juce::OpenGLRenderer
	{
	public:
		explicit SpectrumRenderer(juce::Component& component);
		~SpectrumRenderer();

		
		void newOpenGLContextCreated() override;
		void renderOpenGL() override;
		void openGLContextClosing() override;
		
	private:
		std::unique_ptr<Texture> texture;
		std::unique_ptr<VertexBuffer> vertexBuffer;
		std::unique_ptr<Attributes> attributes;
		std::unique_ptr<Uniforms> uniforms;
		juce::OpenGLContext context;
		std::unique_ptr<juce::OpenGLShaderProgram> shader;
	};
}
