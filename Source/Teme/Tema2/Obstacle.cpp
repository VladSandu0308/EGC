#include "Obstacle.h"

#include <Core/Engine.h>

const GLfloat Obstacle::maxScale = 0.75f;

Obstacle::Obstacle(
	GLfloat _speed,
	GLfloat _amplitude,
	GLfloat _acceleration,
	GLfloat _scale,
	GLboolean _variable
) :
	acceleration(_acceleration),
	variable(_variable)
{
	speed		= _speed;
	amplitude	= _amplitude;
	scale		= _scale;
	speed		= _speed;
	angle		= (GLfloat)M_PI;
	angleOY		= 0.f;
	scaleType	= 1.f;

	obstacle = new Mesh("sphere");
	obstacle->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
}

Obstacle::~Obstacle()
{
	delete obstacle;
}

glm::mat4& Obstacle::GetModelMatrix(GLfloat deltaTimeSeconds)
{
	speed += acceleration * deltaTimeSeconds;
	angle += speed * deltaTimeSeconds;
	angleOY += acceleration * deltaTimeSeconds;

	if (angle >= 360.f)
	{
		angle = 0.f;
	}

	if (angleOY >= 360.f)
	{
		angleOY = 0.f;
	}

	if (variable)
	{
		scale += scaleType * acceleration * deltaTimeSeconds;

		if (scale >= maxScale || scale <= -maxScale)
		{
			scaleType = -scaleType;
		}
	}

	modelMatrix = Transform3D::RotateOZ(RADIANS(angle));
	modelMatrix *= Transform3D::Translate(amplitude * sin(angleOY) + 5.f, 0.f, 0.f);

	return modelMatrix;
}

Mesh* Obstacle::GetMesh()
{
	return obstacle;
}