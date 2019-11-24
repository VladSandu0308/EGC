#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>

#include "Transform3D.h"

class Fuel
{
public:
	Fuel(
		GLfloat _radiusOX,
		GLfloat _radiusOY,
		GLfloat _speed,
		GLfloat _acceleration,
		GLfloat _scale,
		GLfloat _scaleSpeed,
		GLboolean _variable);
	~Fuel();

	glm::mat4& GetModelMatrix(GLfloat deltaTimeSeconds);
	static Mesh* GetMesh();
	static Texture2D* GetTexture();
	static Shader* GetShader();

	static GLvoid Init();

private:
	glm::mat4 modelMatrix;

	static Mesh* obstacle;
	static Texture2D* texture;
	static Shader* shader;

	static const GLfloat maxScale;
	static const GLfloat minScale;

	const GLfloat acceleration;
	const GLboolean variable;
	const GLfloat radiusOX, radiusOY;
	const GLfloat scaleSpeed;

	const GLfloat speedOX, speedOY, speedOZ;

	GLfloat scaleType;
	GLfloat scale;
	GLfloat speed;
	GLfloat angle;
	GLfloat fuelAmount;

	GLfloat angleOX, angleOY, angleOZ;
};
