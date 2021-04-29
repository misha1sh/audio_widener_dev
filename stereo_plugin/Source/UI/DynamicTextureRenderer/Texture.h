#pragma once

#include "JuceHeader.h"

namespace DynamicTextureOpenGL
{
	class Texture
	{
	public:
		Texture(juce::OpenGLContext& context, int width, int height);
		~Texture();
		void bind();
		void change(int offsetx, int offsety, int width, int height, unsigned char* data);
	private:
		juce::OpenGLContext& context;
		
		int width, height;
		std::vector<unsigned char> imageData;

		GLuint tex;

		inline unsigned char& getData(int x, int y, int k);
	};
}