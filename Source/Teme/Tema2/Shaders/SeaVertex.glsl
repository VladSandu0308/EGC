#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

const float frequency = 10;
const float PI = 3.14159;

out vec2 frag_coord;
out vec3 frag_normal;
out vec3 frag_color;
out vec3 frag_position;

void main()
{
	frag_color = v_color;
	frag_normal = mat3(transpose(inverse(Model))) * v_normal;
	frag_coord = v_coord;

	float maxim = max(abs(v_position.x), abs(v_position.y));
	float radius = abs(maxim - 10);
	float distance = length(v_position);
	float deltaY = radius * sin(- PI * distance * frequency + 2 * time);
	float deltaX = radius * cos(time / 2);
	float deltaZ = radius * sin(time);
	gl_Position = Projection * View * Model * vec4(v_position.x + 0.2 * deltaX, v_position.y + 0.5 * deltaY, v_position.z + deltaZ, 1.0);
	frag_position = vec3(Model * vec4(v_position.x + 0.2 * deltaX, v_position.y + 0.5 * deltaY, v_position.z + deltaZ, 1.0));
}