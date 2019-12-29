#version 330
 
uniform sampler2D texture;
 
in vec2 frag_coord;

layout(location = 0) out vec4 out_color;

void main()
{
	/* Calculate the out_color using the texture2D() function */
	out_color = texture2D(texture, frag_coord);
}