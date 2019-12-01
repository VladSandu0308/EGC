#pragma once

#include <Component/SimpleScene.h>

#include "Aeroplane.h"
#include "Obstacle.h"
#include "Fuel.h"
#include "FuelBar.h"
#include "Cloud.h"
#include "Sea.h"
#include "Heart.h"

#include "Transform3D.h"
#include "LabCamera.h"

class PlaneRunner : public SimpleScene
{
public:
	PlaneRunner();
	~PlaneRunner();

	void Init() override;

private:
	GLvoid FrameStart() override;
	GLvoid Update(float deltaTimeSeconds) override;
	GLvoid FrameEnd() override;

	/* Renders a given mesh */
	GLvoid RenderMesh(
		Mesh* mesh,
		Shader* shader,
		const glm::mat4& modelMatrix
	);

	/* Renders a given mesh by applying a custom texture to it */
	GLvoid RenderTexturedMesh(
		Mesh* mesh,
		Shader* shader,
		const glm::mat4& modelMatrix,
		Texture2D* texture);

	/* Calculates the plane's movement */
	GLvoid MovePlane(GLfloat deltaTimeSeconds);

	/* Calls the function bellow in order to render the plane mesh by mesh */
	GLvoid RenderPlane(GLfloat deltaTimeSeconds);
	GLvoid RenderPlanePart(
		Mesh* mesh,
		GLfloat offsetX,
		GLfloat offsetY,
		GLfloat offsetZ
	);

	/* Renders the obstacles one by one */
	GLvoid RenderObstacles(GLfloat deltaTimeSeconds);

	/* Checks if the object with the given model matrix collides with the plane */
	GLboolean CheckCollision(glm::mat4& model, GLfloat radius);

	/* Renders the fuel cans one by one */
	GLvoid RenderFuelCans(GLfloat deltaTimeSeconds);

	/* Renders the fuel bar */
	GLvoid RenderFuelBar(GLfloat deltaTimeSeconds);

	/* Renders the clouds one by one */
	GLvoid RenderClouds(GLfloat deltaTimeSeconds);

	/* Renders the seas (both of them) */
	GLvoid RenderSea(GLfloat deltaTimeSeconds);

	/* Renders the remaining lives */
	GLvoid RenderLives(GLfloat deltaTimeSeconds);

	GLvoid OnKeyPress(int key, int mods) override;
	GLvoid OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;

protected:
	const GLfloat zNear, zFar;
	const GLushort numFuelCans, numObstacles, numClouds;

	Plane::Camera* camera;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
	glm::mat4 cockpitMatrix;
	glm::mat4 targetMatrix;

	const GLfloat centreX, centreZ;
	const GLfloat propellerAcceleration;
	const GLfloat planeAcceleration;

	GLfloat mouseCrtX, mouseCrtY;

	GLfloat centreY;
	GLfloat angle;
	GLfloat propellerAngle;
	GLfloat propellerSpeed;
	GLfloat planeSpeed;

	Aeroplane* plane;
	FuelBar* fuelBar;
	Sea* sea;
	Sea* revSea;
	Heart* heart;

	std::vector<Obstacle> obstacles;
	std::vector<Fuel> fuelCans;
	std::vector<Cloud> clouds;

	GLboolean render;
	GLushort cameraType;

	glm::vec3 lightPosition;

	GLint numLives;

	GLfloat deltaXLeft, deltaXRight;
	GLfloat deltaYDown, deltaYUp;

	GLfloat bBoxMinX, bBoxMaxX;
	GLfloat bBoxMinY, bBoxMaxY;
};