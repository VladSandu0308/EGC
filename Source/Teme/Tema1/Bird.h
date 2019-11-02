#pragma once

#include <Core/Engine.h>

class Bird
{
public:
	Bird();
	~Bird();

	/* Getters for the various sizes (radii) of the body parts */
	GLvoid GetHeadRadius(GLfloat& radius);
	GLvoid GetBodyRadii(GLfloat& radiusX, GLfloat& radiusY);

	/* Getters for the meshes comprising the bird */
	Mesh* GetHeadMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* GetBodyMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* GetEyeMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* GetWingMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* GetTailMesh(GLfloat& offsetX, GLfloat& offsetY);
	Mesh* GetBeakMesh(GLfloat& offsetX, GLfloat& offsetY);

	/* Getters for the hitBox */
	Mesh* GetHitBoxMesh(GLfloat& offsetX, GLfloat& offsetY);
	const std::vector<std::pair<GLfloat, GLfloat>>& GetHitBox();
	GLfloat GetHitBoxRadius();

	/* Simulates the bird's flight by flapping its wing */
	void FlapWing(GLfloat deltaTimeSeconds);

private:
	const GLfloat headRadius;
	const GLfloat bodyRadiusX;
	const GLfloat bodyRadiusY;
	const GLfloat eyeRadius;
	const GLushort numTriangles;
	const GLushort numTrianglesHBox;
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