#pragma once

#include "JuceHeader.h"

namespace SpectrumOpenGL
{
	class Texture
	{
	public:
		Texture(juce::OpenGLContext& context, int width, int height);
		~Texture();
		void bind();
		void change();
	private:
		juce::OpenGLContext& context;
		
		int width, height;
		std::vector<unsigned char> imageData;

		GLuint tex;
	};
}