#include "DynamicTextureRenderer.h"
#include "SpectrumShaders.h"

using namespace DynamicTextureOpenGL;





DynamicTextureRenderer::DynamicTextureRenderer(juce::Component& component, int _width, int _height):
	width(_width), height(_height), columnsToAddCount(0)
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
		texture.reset(new Texture(context, width, height));
	}
	else
	{
		DBG("Failed to create shader: " + shader->getLastError());
		jassertfalse;
	}

}

float f = 0.0f;
void DynamicTextureRenderer::renderOpenGL()
{
	
	glClear(GL_COLOR_BUFFER_BIT);

	if (columnsToAddCount > 0)
	{
		
	}
	
	shader->use();
	vertexBuffer->bind();
	attributes->enable(context);
	texture->bind();

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





