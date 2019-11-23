#pragma once

#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>

#include "Aeroplane.h"

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
};