#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 frag_normal;
out vec3 frag_color;
out vec3 frag_position;

void main()
{
	// Pass v_texture_coord as output to Fragment Shader

	frag_color = v_color;
	frag_position = v_position;
	frag_normal = v_normal;

	gl_Position = Projection * View * Model * vec4(v_position, 1.f);
}