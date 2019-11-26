#version 330
 
uniform sampler2D texture;
 
in vec2 frag_coord;
in vec3 frag_normal;
in vec3 frag_color;
in vec3 frag_position;

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(frag_color, .5f);
}