#pragma once

#include <JuceHeader.h>

#include "Attributes.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "Uniforms.h"

namespace DynamicTextureOpenGL
{
	class DynamicTextureRenderer final : private juce::OpenGLRenderer
	{
	public:
		explicit DynamicTextureRenderer(juce::Component& component, int width, int height);
		~DynamicTextureRenderer() override;

		
		void newOpenGLContextCreated() override;
		void renderOpenGL() override;
		void openGLContextClosing() override;

		void changeTexture(int offsetx, int offsety, int width, int height, unsigned char* data);
		void addColumn(unsigned char* data);
	private:
		std::unique_ptr<Texture> texture;
		std::unique_ptr<VertexBuffer> vertexBuffer;
		std::unique_ptr<Attributes> attributes;
		std::unique_ptr<Uniforms> uniforms;
		juce::OpenGLContext context;
		std::unique_ptr<juce::OpenGLShaderProgram> shader;

		int columnsToAddCount;
		std::vector<unsigned char> columnsToAdd;

		int width, height;
	};
}
