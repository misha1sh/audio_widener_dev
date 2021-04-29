#pragma once
#include "JuceHeader.h"


namespace SpectrumOpenGL
{
	class VertexBuffer
	{
	public:
		explicit VertexBuffer(juce::OpenGLContext& context);
		~VertexBuffer();

		void bind();
	private:
		GLuint vertexBufferID;
		juce::OpenGLContext& context;
	};

}
