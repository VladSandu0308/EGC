#pragma once

#include "FuelBar.h"

FuelBar::FuelBar() :
	maxFuel(100.f), decay(8.f)
{
	crtFuel = maxFuel;

	/* Generate the background */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(3.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(3.f, .5f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.f, .5f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		background = Utils::CreateMesh("background", vertices, indices);
	}

	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(3.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(3.f, .5f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(0.f, .5f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		fuel = Utils::CreateMesh("fuel", vertices, indices);
	}

	{
		shader = new Shader("CloudShader");
		shader->AddShader("Source/Teme/Tema2/Shaders/FuelBarVertex.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Teme/Tema2/Shaders/FuelBarFragment.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
	}
}

FuelBar::~FuelBar()
{
	delete background;
	delete fuel;
	delete shader;
}

Mesh* FuelBar::GetBackground()
{
	return background;
}

Mesh* FuelBar::GetFuel(
	GLfloat update,
	GLfloat deltaTimeSeconds,
	GLfloat& scaleFactor
)
{
	crtFuel -= decay * deltaTimeSeconds - update;
	crtFuel = crtFuel > maxFuel ? maxFuel : crtFuel;
	crtFuel = crtFuel < 0.f ? 0.f : crtFuel;

	scaleFactor = crtFuel / maxFuel;

	return fuel;
}

Shader* FuelBar::GetShader()
{
	return shader;
}