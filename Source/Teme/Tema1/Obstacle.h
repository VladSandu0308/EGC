#pragma once

#include <Core/Engine.h>

class Obstacle
{
public:
	Obstacle(GLfloat width, GLfloat height, const std::string& name);
	~Obstacle();

	/* Returns the created mesh */
	Mesh* GetMesh();

private:
	Mesh* mObstacle;
};