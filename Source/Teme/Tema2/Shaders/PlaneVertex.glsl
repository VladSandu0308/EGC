#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;
out vec3 object_color;

void main()
{
	// Compute world space vertex position and normal
	// Send world position and world normal to Fragment Shader
	world_position	= (Model * vec4(v_position, 1)).xyz;
	world_normal	= normalize( mat3(Model) * normalize(v_normal));
	object_color	= v_color;

	gl_Position		= Projection * View * Model * vec4(v_position, 1.f);
}
