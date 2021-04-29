#include "Texture.h"


DynamicTextureOpenGL::Texture::Texture(juce::OpenGLContext& _context, int _width, int _height):
	context(_context),
	width(_width), height(_height),
	imageData(width*height * 3, 0)
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);	
/*	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (i < 100 && j < 10)
				{
					continue;
				}
				getData(i, j, k) = ((i + j) * (k + 1));
			}
		}
	}*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, &imageData[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

DynamicTextureOpenGL::Texture::~Texture()
{
	glDeleteTextures(1, &tex);
}

void DynamicTextureOpenGL::Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, tex);
}

unsigned char& DynamicTextureOpenGL::Texture::getData(int x, int y, int k)
{
	return imageData[x * height * 3 + y * 3 + k];
}

void DynamicTextureOpenGL::Texture::change(int offsetx, int offsety, int changeWidth, int changeHeight, unsigned char* data)
{
	jassert(changeHeight % 4 == 0);
	for (int x = 0; x < changeWidth; x++)
	{
		memcpy(&imageData[(offsetx + x) * height * 3 + offsety * 3], data + x * changeHeight * 3, changeHeight * 3);
	}
	bind();

	glTexSubImage2D(GL_TEXTURE_2D, 0, offsety, offsetx, changeHeight, changeWidth, GL_RGB, GL_UNSIGNED_BYTE, data);

	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &imageData[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
}
