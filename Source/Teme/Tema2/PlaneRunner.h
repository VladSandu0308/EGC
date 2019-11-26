#pragma once

#include <Component/SimpleScene.h>

#include "Aeroplane.h"
#include "Obstacle.h"
#include "Fuel.h"
#include "FuelBar.h"
#include "Cloud.h"

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

	GLvoid RenderSimpleMesh(
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

	/* Renders the fuel cans one by one */
	GLvoid RenderFuelCans(GLfloat deltaTimeSeconds);

	/* Renders the fuel bar */
	GLvoid RenderFuelBar(GLfloat deltaTimeSeconds);

	/* Renders the clouds one by one */
	GLvoid RenderClouds(GLfloat deltaTimeSeconds);

	GLvoid OnInputUpdate(float deltaTime, int mods) override;
	GLvoid OnKeyPress(int key, int mods) override;
	GLvoid OnKeyRelease(int key, int mods) override;
	GLvoid OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	GLvoid OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	GLvoid OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	GLvoid OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	GLvoid OnWindowResize(int width, int height) override;

protected:
	const GLfloat zNear, zFar;
	Plane::Camera* camera;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;

	const GLfloat centreX, centreZ;
	const GLfloat propellerAcceleration;
	const GLfloat planeAcceleration;

	GLfloat mouseStartX, mouseStartY;
	GLfloat mouseCrtX, mouseCrtY;

	GLfloat centreY;
	GLfloat angle;
	GLfloat propellerAngle;
	GLfloat propellerSpeed;
	GLfloat planeSpeed;

	Aeroplane* plane;
	FuelBar* fuelBar;

	std::vector<Obstacle> obstacles;
	std::vector<Fuel> fuelCans;
	std::vector<Cloud> clouds;

	GLboolean render;

	glm::vec3 lightPosition;
	glm::vec3 lightDirection;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;

	GLint typeOfLight;
	GLfloat angleOX, angleOY;
	GLfloat cutoffAngle;
};