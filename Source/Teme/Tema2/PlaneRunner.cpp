#pragma once

#include "PlaneRunner.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

PlaneRunner::PlaneRunner() :
	zNear(0.01f), zFar(200.f),
	centreX(-5.f), centreZ(0.f),
	propellerAcceleration(20.f),
	planeAcceleration(10.f)
{
}

PlaneRunner::~PlaneRunner()
{
}

void PlaneRunner::Init()
{
	glm::ivec2 resolution = window->GetResolution();

	plane			= new Aeroplane();

	angle			= 0.f;
	propellerAngle	= 0.f;
	centreY			= 1.75f;
	planeSpeed		= 4.f;
	propellerSpeed	= 100.f;

	// Create a shader program for drawing face polygon with the color of the normal
	{
		/*Shader* shader = new Shader("ShaderLab6");
		shader->AddShader("Source/Laboratoare/PlaneRunner/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/PlaneRunner/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;*/
	}

	camera = new Plane::Camera();
	camera->Set(
		glm::vec3(0.f, 3.f, 10.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f)
	);

	projectionMatrix = glm::perspective(
		RADIANS(60.f),
		window->props.aspectRatio,
		zNear,
		zFar
	);
}

void PlaneRunner::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(.529f, .808f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void PlaneRunner::Update(float deltaTimeSeconds)
{
	MovePlane(deltaTimeSeconds);
	RenderPlane(deltaTimeSeconds);
}

GLvoid PlaneRunner::MovePlane(GLfloat deltaTimeSeconds)
{
	// TODO: fa-o corect
	angle = 5.f * atan(
		(mouseCrtX - centreX)
		/ (mouseCrtY - centreY + FLT_EPSILON)
	);

	centreY += planeSpeed * deltaTimeSeconds * sin(angle);

	propellerSpeed += propellerAcceleration * deltaTimeSeconds;
	propellerAngle += propellerSpeed * deltaTimeSeconds;

	if (propellerAngle >= 360.f)
	{
		propellerAngle = 0.f;
	}
}


GLvoid PlaneRunner::RenderPlane(GLfloat deltaTimeSeconds)
{
	GLfloat offsetX, offsetY, offsetZ;

	RenderPlanePart(
		plane->GetPropeller(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);
	RenderPlanePart(
		plane->GetNose(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);
	RenderPlanePart(
		plane->GetBody(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);
	RenderPlanePart(
		plane->GetCockpit(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);
	RenderPlanePart(
		plane->GetTail(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);
	RenderPlanePart(
		plane->GetWing(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);
	RenderPlanePart(
		plane->GetRudder(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);
	RenderPlanePart(
		plane->GetRudderWing(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);
}

GLvoid PlaneRunner::RenderPlanePart(
	Mesh* planePart,
	GLfloat offsetX,
	GLfloat offsetY,
	GLfloat offsetZ
)
{
	modelMatrix = Transform3D::Translate(centreX, centreY, centreZ);
	modelMatrix *= Transform3D::RotateOZ(angle);
	modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
	modelMatrix *= Transform3D::Translate(offsetX, offsetY, offsetZ);

	if (!strcmp(planePart->GetMeshID(), "propeller")
		|| !strcmp(planePart->GetMeshID(), "nose"))
	{
		modelMatrix *= Transform3D::RotateOX(RADIANS(propellerAngle));
	}

	RenderSimpleMesh(planePart, shaders["VertexColor"], modelMatrix);
}

void PlaneRunner::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void PlaneRunner::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// get shader location for uniform mat4 "Model"
	GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");

	// set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// get shader location for uniform mat4 "View"
	GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");

	// set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// get shader location for uniform mat4 "Projection"
	GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");

	// set shader uniform "Projection" to projectionMatrix
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// get shader location for "Time"
	GLint timeLocation = glGetUniformLocation(shader->GetProgramID(), "Time");

	// set shader uniform "Time" to elapsed time
	glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());

	//glm::vec3 eyePosition = camera->position;

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void PlaneRunner::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W))
		{
			// Translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_A))
		{
			// Translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_S))
		{
			// Translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_D))
		{
			// Translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_Q))
		{
			// Translate the camera down
			camera->TranslateUpward(-deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_E))
		{
			// Translate the camera up
			camera->TranslateUpward(deltaTime * cameraSpeed);
		}
	}
}

void PlaneRunner::OnKeyPress(int key, int mods)
{
	// add key press event
}

void PlaneRunner::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void PlaneRunner::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0)
		{
			// Rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// Use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL)
		{
			// Rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// Use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}
	}

	// TODO: transpune din pixeli in pozitii
	mouseCrtX = (GLfloat)mouseX;
	mouseCrtY = (GLfloat)mouseY;
}

void PlaneRunner::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void PlaneRunner::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void PlaneRunner::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void PlaneRunner::OnWindowResize(int width, int height)
{
}
