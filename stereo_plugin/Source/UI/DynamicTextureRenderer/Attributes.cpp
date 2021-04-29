#include "Attributes.h"


using namespace DynamicTextureOpenGL;

Attributes::Attributes(juce::OpenGLContext& context, juce::OpenGLShaderProgram& shader)
{
	position.reset(createAttribute(context, shader, "position"));
}

void Attributes::enable(juce::OpenGLContext& context)
{
	jassert(position.get() != nullptr);

	context.extensions.glEnableVertexAttribArray(position->attributeID);

	
	context.extensions.glVertexAttribPointer(position->attributeID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
}

void Attributes::disable(juce::OpenGLContext& context)
{
	jassert(position.get() != nullptr);
	context.extensions.glDisableVertexAttribArray(position->attributeID);
}

juce::OpenGLShaderProgram::Attribute* Attributes::createAttribute(juce::OpenGLContext& context,
                                                                  juce::OpenGLShaderProgram& shader, const juce::String& attributeName)

{
	if (context.extensions.glGetAttribLocation(shader.getProgramID(), attributeName.toRawUTF8()) < 0)
	{
		DBG("Unable to find attribute " + attributeName + " in spectrum shader");
		jassertfalse;
	}

	return new juce::OpenGLShaderProgram::Attribute(shader, attributeName.toRawUTF8());
}


