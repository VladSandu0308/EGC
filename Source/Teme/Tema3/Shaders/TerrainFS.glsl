#version 330
 
uniform sampler2D heightTexture;
 
in vec2 frag_coord;
in vec3 frag_normal;
in vec3 frag_color;
in vec3 frag_position;

layout(location = 0) out vec4 out_color;

void main()
{
	// calculate the out_color using the texture2D() function
	out_color = texture2D(heightTexture, frag_coord);
}