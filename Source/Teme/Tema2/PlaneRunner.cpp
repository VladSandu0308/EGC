#pragma once

#include "PlaneRunner.h"

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

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
	delete camera;
	delete plane;
	delete fuelBar;
}

void PlaneRunner::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	srand(time(NULL));

	plane			= new Aeroplane();
	fuelBar			= new FuelBar();

	angle			= 0.f;
	propellerAngle	= 0.f;
	centreY			= 1.75f;
	planeSpeed		= 4.f;
	propellerSpeed	= 100.f;
	render			= GL_TRUE;

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

	{
		Obstacle::Init();
		Fuel::Init();
		Cloud::Init();

		obstacles.emplace_back();
		obstacles.emplace_back();
		obstacles.emplace_back();
		obstacles.emplace_back();

		fuelCans.emplace_back();
		fuelCans.emplace_back();
		fuelCans.emplace_back();

		clouds.emplace_back();
		clouds.emplace_back();
		clouds.emplace_back();
		clouds.emplace_back();
		clouds.emplace_back();
		clouds.emplace_back();
		clouds.emplace_back();
		clouds.emplace_back();
	}

	{
		lightPosition = glm::vec3(0, 1, 1);
		lightDirection = glm::vec3(0, -1, 0);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;

		typeOfLight = 0;
		angleOX = 0.f;
		angleOY = 0.f;
		cutoffAngle = 30.f;
	}
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
	GLfloat deltaTime;

	if (render == GL_TRUE)
	{
		MovePlane(deltaTimeSeconds);
		deltaTime = deltaTimeSeconds;
	}
	else
	{
		deltaTime = 0.f;
	}

	RenderPlane(deltaTime);
	RenderFuelCans(deltaTime);
	RenderObstacles(deltaTime);
	RenderFuelBar(deltaTime);
	RenderClouds(deltaTime);
}

GLvoid PlaneRunner::MovePlane(GLfloat deltaTimeSeconds)
{
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
	GLfloat offsetX = 0.f, offsetY = 0.f, offsetZ = 0.f;

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
	RenderPlanePart(
		plane->GetLight(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);
	RenderPlanePart(
		plane->fmmm(offsetX, offsetY, offsetZ),
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

	if (!strcmp(planePart->GetMeshID(), "light"))
	{
		glm::vec4 pos = modelMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f);

		lightPosition.x = pos.x;
		lightPosition.y = pos.y;
		lightPosition.z = pos.z;
	}

	RenderSimpleMesh(planePart, plane->GetShader(), modelMatrix);
}

GLvoid PlaneRunner::RenderFuelCans(GLfloat deltaTimeSeconds)
{
	for (Fuel& fuel : fuelCans)
	{
		RenderTexturedMesh(
			Fuel::GetMesh(),
			Fuel::GetShader(),
			fuel.GetModelMatrix(deltaTimeSeconds),
			Fuel::GetTexture()
		);
	}
}

GLvoid PlaneRunner::RenderObstacles(GLfloat deltaTimeSeconds)
{
	for (Obstacle& obs : obstacles)
	{
		RenderTexturedMesh(
			Obstacle::GetMesh(),
			Obstacle::GetShader(),
			obs.GetModelMatrix(deltaTimeSeconds),
			Obstacle::GetTexture()
		);
	}
}

GLvoid PlaneRunner::RenderFuelBar(GLfloat deltaTimeSeconds)
{
	GLfloat scaleFactor;

	RenderSimpleMesh(
		fuelBar->GetBackground(),
		fuelBar->GetShader(),
		Transform3D::Translate(-1.5f, 5.5f, 0.f)
	);

	Mesh* fuel = fuelBar->GetFuel(0.f, deltaTimeSeconds, scaleFactor);

	RenderSimpleMesh(
		fuel,
		fuelBar->GetShader(),
		Transform3D::Translate(-1.5f, 5.5f, 0.001f)
		* Transform3D::Scale(scaleFactor, 1.f, 1.f)
	);
}

GLvoid PlaneRunner::RenderClouds(GLfloat deltaTimeSeconds)
{
	Mesh* cloudMesh			= Cloud::GetMesh();
	Texture2D* cloudTexture = Cloud::GetTexture();
	Shader* cloudShader		= Cloud::GetShader();

	GLushort numParts;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (Cloud& cloud : clouds)
	{
		numParts = cloud.GetPartsNumber(deltaTimeSeconds);

		for (int i = 0; i != numParts; ++i)
		{
			RenderTexturedMesh(
				cloudMesh,
				cloudShader,
				cloud.GetModelMatrix(i),
				cloudTexture
			);
		}
	}

	glDisable(GL_BLEND);
}

void PlaneRunner::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

GLvoid PlaneRunner::RenderTexturedMesh(
	Mesh* mesh,
	Shader* shader,
	const glm::mat4& modelMatrix,
	Texture2D* texture
)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(
		loc_view_matrix,
		1,
		GL_FALSE,
		glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(
		shader->program,
		"Projection");
	glUniformMatrix4fv(
		loc_projection_matrix,
		1,
		GL_FALSE,
		glm::value_ptr(projectionMatrix));

	// Activate texture location 0
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture1 ID
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	// Send texture uniform value
	glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(
		mesh->GetDrawMode(),
		static_cast<int>(mesh->indices.size()),
		GL_UNSIGNED_SHORT,
		0);
}

void PlaneRunner::RenderSimpleMesh(
	Mesh* mesh,
	Shader* shader,
	const glm::mat4& modelMatrix
)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	// Render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// Set light position uniform
	int light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

	// Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->position;
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	// Set material property uniforms (shininess, kd, ks, object color) 
	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	GLint type = glGetUniformLocation(shader->program, "type_of_light");
	glUniform1i(type, typeOfLight);

	GLint cut_off_angle = glGetUniformLocation(shader->program, "cut_off_angle");
	glUniform1f(cut_off_angle, cutoffAngle);

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
	if (key == GLFW_KEY_P)
	{
		render = !render;
	}
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
