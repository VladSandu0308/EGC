#pragma once

#include "Cloud.h"

Mesh* Cloud::mesh			= nullptr;
Texture2D* Cloud::texture	= nullptr;
Shader* Cloud::shader		= nullptr;

Cloud::Cloud()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	
	std::uniform_int_distribution<GLushort> partsDist(3, 7);
	std::uniform_real_distribution<GLfloat> angleDist(0.f, 360.f);
	std::uniform_real_distribution<GLfloat> speedDist(1.f, 2.f);
	std::uniform_real_distribution<GLfloat> radiusDistOX(7.f, 15.f);
	std::uniform_real_distribution<GLfloat> radiusDistOY(5.f, 8.f);
	std::uniform_real_distribution<GLfloat> deltaRadiusDist(-1.f, 1.f);
	std::uniform_real_distribution<GLfloat> deltaAngleDist(-10.f, 10.f);
	std::uniform_real_distribution<GLfloat> scaleDist(.75f, 1.5f);

	numParts	= partsDist(gen);
	angle		= angleDist(gen);
	speed		= speedDist(gen);
	radiusOX	= radiusDistOX(gen);
	radiusOY	= radiusDistOY(gen);

	for (int i = 0; i != numParts; ++i)
	{
		deltaAngles.push_back(deltaAngleDist(gen));
		deltaRadiiOX.push_back(deltaRadiusDist(gen));
		deltaRadiiOY.push_back(deltaRadiusDist(gen));
		scales.push_back(scaleDist(gen));
	}
}

Cloud::~Cloud()
{
}

GLushort Cloud::GetPartsNumber(GLfloat deltaTimeSeconds)
{
	angle += speed * deltaTimeSeconds;
	angle = angle > 360.f ? 0.f : angle;

	return numParts;
}

glm::mat4& Cloud::GetModelMatrix(GLushort part)
{
	modelMatrix = Transform3D::Translate(
		(radiusOX + deltaRadiiOX[part]) * cos(RADIANS(angle + deltaAngles[part])),
		(radiusOY + deltaRadiiOX[part]) * sin(RADIANS(angle + deltaAngles[part])),
		-5.f
	);
	modelMatrix *= Transform3D::Scale(scales[part], scales[part], scales[part]);

	return modelMatrix;
}

GLvoid Cloud::Init()
{
	mesh = new Mesh("cloud");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");

	texture = new Texture2D();
	texture->Load2D("Source/Teme/Tema2/Textures/cloud.jpg");

	shader = new Shader("CloudShader");
	shader->AddShader("Source/Teme/Tema2/Shaders/ObjectVertex.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Teme/Tema2/Shaders/ObjectFragment.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
}

Mesh* Cloud::GetMesh()
{
	return mesh;
}

Texture2D* Cloud::GetTexture()
{
	return texture;
}

Shader* Cloud::GetShader()
{
	return shader;
}