#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include <iostream>
#include <algorithm>

using namespace std;

class Bird : public SimpleScene
{
public:
	Bird();
	~Bird();

	Mesh* getHeadMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getBodyMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getEyeMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getWingMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getTailMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getBeakMesh(GLfloat& offsetX, GLfloat& offsetY);

	void FlapWing(float deltaTimeSeconds);

private:
	const GLfloat radius;
	const GLfloat scale;
	const GLuint numTriangles;

	const GLfloat wingSpeed;
	GLfloat wingDirection;
	GLfloat wingHeight;

	GLfloat headOffsetX, headOffsetY;
	GLfloat bodyOffsetX, bodyOffsetY;
	GLfloat eyeOffsetX, eyeOffsetY;
	GLfloat wingOffsetX, wingOffsetY;
	GLfloat tailOffsetX, tailOffsetY;
	GLfloat beakOffsetX, beakOffsetY;
};