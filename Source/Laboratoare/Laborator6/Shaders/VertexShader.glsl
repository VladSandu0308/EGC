#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main()
{
	// send output to fragment shader
	frag_position	= v_position;
	frag_normal		= v_normal + vec3(sin(Time), cos(Time), 1.0);
	frag_texture	= v_texture;
	frag_color		= v_color;

	// compute gl_Position
	vec3 v_pos_final = v_position + vec3(sin(Time), 0, cos(Time));
	gl_Position = Projection * View * Model * vec4(v_pos_final, 1.0);
}
