#include "DynamicTextureRenderer.h"
#include "SpectrumShaders.h"

using namespace DynamicTextureOpenGL;





DynamicTextureRenderer::DynamicTextureRenderer(juce::Component& component)
{
	context.setRenderer(this);
	context.attachTo(component);
	context.setContinuousRepainting(true);
}

DynamicTextureRenderer::~DynamicTextureRenderer()
{
	context.detach();
}

void DynamicTextureRenderer::newOpenGLContextCreated()
{
	vertexBuffer.reset(new VertexBuffer(context));
	
	shader.reset(new juce::OpenGLShaderProgram(context));
	if (shader->addVertexShader(juce::OpenGLHelpers::translateVertexShaderToV3(VertexShader))          // [2]
		&& shader->addFragmentShader(juce::OpenGLHelpers::translateFragmentShaderToV3(FragmentShader))
		&& shader->link())
	{
		shader->use();
		attributes.reset(new Attributes(context, *shader));
		uniforms.reset(new Uniforms(context, *shader));
		texture.reset(new Texture(context, 128, 128));
	}
	else
	{
		DBG("Failed to create shader: " + shader->getLastError());
		jassertfalse;
	}

}

std::vector<unsigned char> ddata;
float f = 0.0f;
void DynamicTextureRenderer::renderOpenGL()
{
	
	glClear(GL_COLOR_BUFFER_BIT);

	int t = juce::Time::currentTimeMillis();

	/*
 *	int offsetx = t % 128;
	int offsety = (t + 45) % 128;*/
	/*int offsetx = 50;
	int offsety = 15;
	int width = 15; // t % (128 - offsetx);
	int height = 50; // t % (128 - offsety);
	*/

	int offsetx = 7;
	int offsety = 21;
	int width = 31;
	int height = 36;
	
	ddata.resize(128 * 128 * 3);
	int pos = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
		/*	for (int k = 0; k < 3; k++)
			{
				ddata[pos++] = i * (k + 1) + j * (k + 2);
			}*/
			/*ddata[pos++] = i * 3;
			ddata[pos++] = j * 3;
			ddata[pos++] = 0;*/
			ddata[pos++] = i * 4;
			ddata[pos++] = j * 2;
			ddata[pos++] = 0;
		}
	}
	texture->change(offsetx, offsety, width, height, &ddata[0]);

	shader->use();
	vertexBuffer->bind();
	attributes->enable(context);
	texture->bind();
//	context.extensions.glUniform1f(uniforms->offsetX->uniformID, f += 0.01f);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	attributes->disable(context);
}

void DynamicTextureRenderer::openGLContextClosing()
{
	shader.reset();
	vertexBuffer.reset();
	attributes.reset();
	texture.reset();
}





