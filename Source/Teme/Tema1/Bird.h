#pragma once

#include <Core/Engine.h>

class Bird
{
public:
	Bird();
	~Bird();

	GLvoid getHeadRadius(GLfloat& radius);
	GLvoid getBodyRadii(GLfloat& radiusX, GLfloat& radiusY);

	Mesh* getHeadMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getBodyMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getEyeMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getWingMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getTailMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* getBeakMesh(GLfloat& offsetX, GLfloat& offsetY);

	Mesh* getHitBoxMesh(GLfloat& offsetX, GLfloat& offsetY);
	const std::vector<std::pair<GLfloat, GLfloat>>& getHitBox();
	GLfloat getHitBoxRadius();

	void FlapWing(GLfloat deltaTimeSeconds);

private:
	const GLfloat headRadius;
	const GLfloat bodyRadiusX;
	const GLfloat bodyRadiusY;
	const GLfloat eyeRadius;
	const GLuint numTriangles;
	const GLfloat hitBoxRadiusX;
	const GLfloat hitBoxRadiusY;

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

	Mesh* mHitBox;
	std::vector<std::pair<GLfloat, GLfloat>> hitBox;

	GLfloat headOffsetX, headOffsetY;
	GLfloat bodyOffsetX, bodyOffsetY;
	GLfloat eyeOffsetX, eyeOffsetY;
	GLfloat wingOffsetX, wingOffsetY;
	GLfloat tailOffsetX, tailOffsetY;
	GLfloat beakOffsetX, beakOffsetY;

	GLfloat hitBoxOffsetX, hitBoxOffsetY;
};