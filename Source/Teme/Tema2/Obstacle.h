#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <random>

#include "Transform3D.h"

class Obstacle
{
public:
	Obstacle();
	~Obstacle() = default;

	/**
	* Calculates the movement of the obstacle as a model matrix and returns
	* it
	*/
	glm::mat4& GetModelMatrix(GLfloat deltaTimeSeconds);

	/* Returns the radius of the obstacle */
	GLfloat GetRadius();

	/* Returns the obstacle mesh */
	static Mesh* GetMesh();

	/* Returns the obstacle texture */
	static Texture2D* GetTexture();

	/* Returns the obstacle shader */
	static Shader* GetShader();

	/* Initialises the mesh, shader and texture used to render the jerry can */
	static GLvoid Init();

private:
	glm::mat4 modelMatrix;

	static Mesh* mesh;
	static Texture2D* texture;
	static Shader* shader;

	static const GLfloat maxScale;
	static const GLfloat minScale;

	GLfloat acceleration;
	GLboolean variable;
	GLfloat radiusOX, radiusOY;
	GLfloat scaleSpeed;

	GLfloat speedOX, speedOY, speedOZ;

	GLfloat scaleType;
	GLfloat scale;
	GLfloat speed;
	GLfloat angle;

	GLfloat angleOX, angleOY, angleOZ;
};