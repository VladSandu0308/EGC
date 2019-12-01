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
}

FuelBar::~FuelBar()
{
	delete background;
	delete fuel;
}

GLvoid FuelBar::AddFuel(GLfloat amount)
{
	crtFuel += amount;
	crtFuel = crtFuel > maxFuel ? maxFuel : crtFuel;
}

Mesh* FuelBar::GetBackground()
{
	return background;
}

GLboolean FuelBar::HasFuel(GLfloat deltaTimeSeconds)
{
	crtFuel -= decay * deltaTimeSeconds;
	crtFuel = crtFuel > maxFuel ? maxFuel : crtFuel;
	crtFuel = crtFuel < 0.f ? 0.f : crtFuel;

	return crtFuel > 0.f;
}

Mesh* FuelBar::GetFuel(
	GLfloat deltaTimeSeconds,
	GLfloat& scaleFactor
)
{
	scaleFactor = crtFuel / maxFuel;

	return fuel;
}