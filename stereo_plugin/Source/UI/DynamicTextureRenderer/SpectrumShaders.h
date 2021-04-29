#pragma once

#include <JuceHeader.h>

namespace DynamicTextureOpenGL
{
	inline juce::String VertexShader = R"(
		#version 150 core
	    in vec2 position;
	
		uniform float offsetX;
	
	    out vec2 texturePosition;
	    void main()
	    {
	        texturePosition = vec2( (position.y + 1.0) / 2.0, (position.x + 1.0) / 2.0 + offsetX);
	        gl_Position = vec4(position, 0.0, 1.0);
	    }
	)";

	inline juce::String FragmentShader = R"(
		#version 150 core
	    in vec2 texturePosition;

		uniform sampler2D tex;
	
	    out vec4 outColor;
	    void main()
	    {
	        outColor = texture(tex, texturePosition); 
	    }
	)";
}
//vec4(texturePosition, 0.0, 1.0);