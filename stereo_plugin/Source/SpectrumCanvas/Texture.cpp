#include "Texture.h"
using enum juce::MissingOpenGLDefinitions;


SpectrumOpenGL::Texture::Texture(juce::OpenGLContext& _context, int _width, int _height):
	context(_context),
	width(_width), height(_height),
	imageData(width*height * 3, 0)
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (i < 100 && j < 10)
				{
					continue;
				}
				imageData[i * height * 3 + j * 3 + k] = ((i + j) * (k + 1));
			}
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &imageData[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

SpectrumOpenGL::Texture::~Texture()
{
	glDeleteTextures(1, &tex);
}

void SpectrumOpenGL::Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, tex);
}

void SpectrumOpenGL::Texture::change()
{
	//glTexSubImage2D();
}
