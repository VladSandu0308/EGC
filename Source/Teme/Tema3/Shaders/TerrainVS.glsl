#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform sampler2D heightTexture;

uniform int terrainHeight;
uniform int terrainWidth;

out vec2 frag_coord;
out vec3 world_position;
out vec3 world_normal;

/* Constants */
float texCoordScaleFactor = 3.f;
float heightScaleFactor = 15.f;

void main()
{
	/* Apply the height map */
	float height	= texture2D(heightTexture, v_texture_coord).r;
	vec3 newPos		= v_position;

	newPos.y		= height;

	/* Compute the new normal */
	vec2 texelSize		= vec2(1.f / terrainWidth, 1.f / terrainHeight);
	float heightRight	=  texture2D(
		heightTexture,
		vec2(v_texture_coord.x + texelSize.x, v_texture_coord.y)
	).r;
	float heightUp		= texture2D(
		heightTexture,
		vec2(v_texture_coord.x, texelSize.y + v_texture_coord.y)
	).r;
	float heightX		= height - heightRight;
	float heightZ		= height - heightUp;
	vec3 normal			= normalize(vec3(
		heightScaleFactor * heightX,
		1.f,
		heightScaleFactor * heightZ
	));

	frag_coord		= texCoordScaleFactor * v_texture_coord;
	world_normal	= normalize(mat3(Model) * normalize(normal));
	world_position	= (Model * vec4(newPos, 1.f)).xyz;

	gl_Position		= Projection * View * Model * vec4(newPos, 1.f);
}