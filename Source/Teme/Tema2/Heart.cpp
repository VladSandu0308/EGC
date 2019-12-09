#pragma once

#include "Heart.h"

Heart::Heart() :
	speed(200.f), angle(0.f)
{
	/* Create the mesh, texture and shader for the heart */
	mesh = new Mesh("heart");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "heart.obj");

	texture = new Texture2D();
	texture->Load2D("Source/Teme/Tema2/Textures/heart.png");

	shader = new Shader("CloudShader");
	shader->AddShader("Source/Teme/Tema2/Shaders/ObjectVertex.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Teme/Tema2/Shaders/ObjectFragment.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
}

glm::mat4& Heart::GetModelMatrix(GLfloat deltaTimeSeconds)
{
	/* Rotate the heart around its centre */
	angle += speed * deltaTimeSeconds;
	angle = angle > 360.f ? 0.f : angle;

	modelMatrix = Transform3D::RotateOY(-RADIANS(angle));

	return modelMatrix;
}

Heart::~Heart()
{
	delete mesh;
	delete shader;
	delete texture;
}

Mesh* Heart::GetMesh()
{
	return mesh;
}

Shader* Heart::GetShader()
{
	return shader;
}

Texture2D* Heart::GetTexture()
{
	return texture;
}