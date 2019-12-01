#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

#include "Transform3D.h"
#include "Utils.h"

class Sea
{
public:
	Sea(GLfloat _speed, const char* name);
	~Sea();

	/* Returns the matrix that models the movement of the sea */
	glm::mat4& GetModelMatrix(GLfloat deltaTimeSeconds);

	/* Returns the mesh used by the sea */
	Mesh* GetMesh();

	/* Returns the shader used by the sea */
	Shader* GetShader();

private:
	const GLfloat speed;

	glm::mat4 modelMatrix;

	GLfloat radius, height;
	GLfloat angle;

	Mesh* mesh;
	Shader* shader;
};