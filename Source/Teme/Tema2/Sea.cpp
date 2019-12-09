#pragma once

#include "Sea.h"

Sea::Sea(GLfloat _speed, const char* name) :
	speed(_speed), radius(10.f), height(40.f), angle(0.f)
{
	const GLushort levelGranulation		= 100;
	const GLushort angularGranulation	= 100;

	glm::vec3 colour					= glm::vec3(.3f, 1.f, .9f);

	/* Set the step for level */
	GLfloat deltaLevelStep				= height / levelGranulation;
	GLfloat startZ						= -height / 2.f;

	/* Set step for angle */
	GLfloat deltaAngularStep			= 2.f * (GLfloat)M_PI / angularGranulation;

	std::vector<VertexFormat> vertices;
	std::vector<GLushort>indices;

	vertices.emplace_back(glm::vec3(0.f, 0.f, startZ), colour);

	GLfloat angle;

	/* Cenerate the sea level by level */
	for (GLushort i = 0; i <= levelGranulation; ++i)
	{
		GLfloat posZ = startZ + deltaLevelStep * i;

		/* Generate one disk of the level */
		angle = 0.f;
		for (GLushort j = 0; j < angularGranulation; ++j)
		{
			GLfloat percent = (GLfloat)rand() / (RAND_MAX);
			percent			= (percent < .8f) ? .8f : percent;

			GLfloat posX	= radius * cos(angle);
			GLfloat posY	= percent * radius * sin(angle);

			vertices.emplace_back(glm::vec3(posX, posY, posZ), colour);
			angle += deltaAngularStep;
		}

		if (i == 0)
		{
			for (GLushort j = 1; j <= angularGranulation; ++j)
			{
				indices.emplace_back(0);
				indices.emplace_back(j);
				indices.emplace_back((j + 1) % angularGranulation);
			}

			continue;
		}

		GLushort crtLevel	= i * angularGranulation;
		GLushort prevLevel	= crtLevel - angularGranulation;

		/* Add the indices for the current disk */
		for (GLushort j = 1; j <= angularGranulation; ++j)
		{
			indices.emplace_back(j + crtLevel);
			indices.emplace_back((j + 1) % angularGranulation + prevLevel);
			indices.emplace_back(j + prevLevel);
			indices.emplace_back(j + crtLevel);
			indices.emplace_back((j + 1) % angularGranulation + crtLevel);
			indices.emplace_back((j + 1) % angularGranulation + prevLevel);
		}

		if (i == levelGranulation)
		{
			vertices.emplace_back(glm::vec3(0.f, 0.f, startZ + height), colour);

			for (GLushort j = 1; j <= angularGranulation; ++j)
			{
				indices.emplace_back(crtLevel + angularGranulation + 1);
				indices.emplace_back(j + crtLevel);
				indices.emplace_back((j + 1) % angularGranulation + crtLevel);
			}
		}
	}

	/* Create the mesh and shader for the sea */
	mesh = Utils::CreateMesh(name, vertices, indices);

	shader = new Shader("Sea");
	shader->AddShader(
		"Source/Teme/Tema2/Shaders/SeaVertex.glsl",
		GL_VERTEX_SHADER
	);
	shader->AddShader(
		"Source/Teme/Tema2/Shaders/SeaFragment.glsl",
		GL_FRAGMENT_SHADER
	);
	shader->CreateAndLink();
}

Sea::~Sea()
{
	delete mesh;
	delete shader;
}

glm::mat4& Sea::GetModelMatrix(GLfloat deltaTimeSeconds)
{
	/* Rotate the sea */
	angle += deltaTimeSeconds * speed;
	angle = angle > 2 * M_PI ? 0.f : angle;

	modelMatrix = Transform3D::Translate(0.f, -9.5f, 0.f);
	modelMatrix *= Transform3D::Scale(3.f, 1.f, 1.f);
	modelMatrix *= Transform3D::RotateOZ(angle);

	return modelMatrix;
}

Mesh* Sea::GetMesh()
{
	return mesh;
}

Shader* Sea::GetShader()
{
	return shader;
}