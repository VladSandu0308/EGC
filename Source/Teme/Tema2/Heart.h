#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>

#include "Transform3D.h"

class Heart
{
public:
	Heart();
	~Heart();

	/**
	* Calculates the movement of the obstacle as a model matrix and returns
	* it
	*/
	glm::mat4& GetModelMatrix(GLfloat deltaTimeSeconds);

	/* Returns the obstacle mesh */
	Mesh* GetMesh();

	/* Returns the obstacle texture */
	Texture2D* GetTexture();

	/* Returns the obstacle shader */
	Shader* GetShader();

private:
	const GLfloat speed;

	Mesh* mesh;
	Texture2D* texture;
	Shader* shader;

	glm::mat4 modelMatrix;
	GLfloat angle;
};