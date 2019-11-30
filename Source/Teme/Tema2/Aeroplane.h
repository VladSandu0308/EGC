#pragma once

#include <Component/SimpleScene.h>

#include "Utils.h"

class Aeroplane
{
public:
	Aeroplane();
	~Aeroplane();

	/* Places the limits of the bounding box in the given parameters */
	GLvoid GetBBoxOffsets(
		GLfloat& deltaXRight,
		GLfloat& deltaXLeft,
		GLfloat& deltaYUp,
		GLfloat& deltaYDown
	);

	/* Getters for the various aerolane parts */
	Mesh* GetPropeller(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetNose(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetBody(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetCockpit(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetTail(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetWing(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetRudder(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetRudderWing(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);
	Mesh* GetLight(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);

	/* Returns the shader used by the plane */
	Shader* GetShader();

	Mesh* fmmm(GLfloat& offsetX, GLfloat& offsetY, GLfloat& offsetZ);

	Mesh* fmm;

private:
	const GLfloat offsetPropellerX, offsetPropellerY, offsetPropellerZ;
	const GLfloat offsetNoseX, offsetNoseY, offsetNoseZ;
	const GLfloat offsetBodyX, offsetBodyY, offsetBodyZ;
	const GLfloat offsetCockpitX, offsetCockpitY, offsetCockpitZ;
	const GLfloat offsetTailX, offsetTailY, offsetTailZ;
	const GLfloat offsetWingX, offsetWingY, offsetWingZ;
	const GLfloat offsetRudderX, offsetRudderY, offsetRudderZ;
	const GLfloat offsetRudderWingX, offsetRudderWingY, offsetRudderWingZ;
	const GLfloat offsetLightX, offsetLightY, offsetLightZ;
	const GLfloat fmmx, fmmy, fmmz;


	Shader* shader;

	Mesh* propeller;
	Mesh* nose;
	Mesh* body;
	Mesh* cockpit;
	Mesh* tail;
	Mesh* wing;
	Mesh* rudder;
	Mesh* rudderWing;
	Mesh* light;


};