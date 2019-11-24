#pragma once

#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>

#include "Transform3D.h"

class Obstacle
{
public:
	Obstacle(
		GLfloat _speed,
		GLfloat _amplitude,
		GLfloat _acceleration,
		GLfloat _scale,
		GLboolean _variable);
	~Obstacle();

	glm::mat4& GetModelMatrix(GLfloat deltaTimeSeconds);
	Mesh* GetMesh();

private:
	glm::mat4 modelMatrix;

	Mesh* obstacle;

	static const GLfloat maxScale;
	const GLfloat acceleration;
	const GLboolean variable;

	GLfloat scaleType;
	GLfloat scale;
	GLfloat amplitude;
	GLfloat speed;
	GLfloat angle;
	GLfloat angleOY;
};