#include "SpectrumRenderer.h"
#include "SpectrumShaders.h"

using namespace SpectrumOpenGL;



Uniforms::Uniforms(juce::OpenGLContext& context, juce::OpenGLShaderProgram& shader)
{
}




SpectrumRenderer::SpectrumRenderer(juce::Component& component)
{
	context.setRenderer(this);
	context.attachTo(component);
	context.setContinuousRepainting(true);
}

SpectrumRenderer::~SpectrumRenderer()
{
	context.detach();
}

void SpectrumRenderer::newOpenGLContextCreated()
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

void SpectrumRenderer::renderOpenGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	shader->use();
	vertexBuffer->bind();
	attributes->enable(context);
	texture->bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	attributes->disable(context);
}

void SpectrumRenderer::openGLContextClosing()
{
	shader.reset();
	vertexBuffer.reset();
	attributes.reset();
	texture.reset();
}





