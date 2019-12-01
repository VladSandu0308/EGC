#version 330
  
in vec3 frag_normal;
in vec3 frag_color;
in vec3 frag_position;

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(frag_color, .1f);
}