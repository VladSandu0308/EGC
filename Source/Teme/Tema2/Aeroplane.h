#pragma once

#include <Component/SimpleScene.h>

#include "Utils.h"

class Aeroplane
{
public:
	Aeroplane();
	~Aeroplane();

	/* Getters for the various aerolane parts */
	Mesh* GetPropeller(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetNose(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetBody(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetCockpit(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetTail(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetWing(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetRudder(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetRudderWing(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);

private:
	const GLfloat offsetPropellerX, offsetPropellerY, offsetPropellerZ;
	const GLfloat offsetNoseX, offsetNoseY, offsetNoseZ;
	const GLfloat offsetBodyX, offsetBodyY, offsetBodyZ;
	const GLfloat offsetCockpitX, offsetCockpitY, offsetCockpitZ;
	const GLfloat offsetTailX, offsetTailY, offsetTailZ;
	const GLfloat offsetWingX, offsetWingY, offsetWingZ;
	const GLfloat offsetRudderX, offsetRudderY, offsetRudderZ;
	const GLfloat offsetRudderWingX, offsetRudderWingY, offsetRudderWingZ;

	Mesh* propeller;
	Mesh* nose;
	Mesh* body;
	Mesh* cockpit;
	Mesh* tail;
	Mesh* wing;
	Mesh* rudder;
	Mesh* rudderWing;
};