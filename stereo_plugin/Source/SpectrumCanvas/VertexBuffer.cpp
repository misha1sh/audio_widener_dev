#include "VertexBuffer.h"

#include "Attributes.h"

using namespace SpectrumOpenGL;

Vertex verts[]
{
	{-1.0f, -1.0f},
	{-1.0f, 1.0f},
	{1.0f, -1.0f},
	{1.0f, 1.0f}
};
VertexBuffer::VertexBuffer(juce::OpenGLContext& _context) :
	context(_context)
{
	context.extensions.glGenBuffers(1, &vertexBufferID);
	context.extensions.glBindBuffer(juce::GL_ARRAY_BUFFER, vertexBufferID);
	context.extensions.glBufferData(juce::GL_ARRAY_BUFFER, sizeof(verts), verts, juce::GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	context.extensions.glDeleteBuffers(1, &vertexBufferID);
}

void VertexBuffer::bind()
{
	context.extensions.glBindBuffer(juce::GL_ARRAY_BUFFER, vertexBufferID);
}	