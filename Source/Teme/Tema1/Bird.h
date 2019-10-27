#pragma once

#include <Core/Engine.h>

class Bird
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

	void FlapWing(GLfloat deltaTimeSeconds);

private:
	const GLfloat radius;
	const GLfloat scale;
	const GLuint numTriangles;

	const GLfloat wingAcceleration;
	GLfloat wingSpeed;
	GLfloat wingDirection;
	GLfloat wingHeight;

	Mesh* mBody;
	Mesh* mHead;
	Mesh* mEye;
	Mesh* mBeak;
	Mesh* mWing;
	Mesh* mTail;

	GLfloat headOffsetX, headOffsetY;
	GLfloat bodyOffsetX, bodyOffsetY;
	GLfloat eyeOffsetX, eyeOffsetY;
	GLfloat wingOffsetX, wingOffsetY;
	GLfloat tailOffsetX, tailOffsetY;
	GLfloat beakOffsetX, beakOffsetY;
};