#pragma once

#include <Core/Engine.h>

class Obstacle
{
public:
	Obstacle(GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b);
	~Obstacle();

	/* Returns the created mesh */
	Mesh* GetMesh();

private:
	Mesh* mObstacle;
};