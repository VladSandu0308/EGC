#include "Laborator5.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator5::Laborator5()
{
}

Laborator5::~Laborator5()
{
}

void Laborator5::Init()
{
	renderCameraTarget	= false;
	projectionType		= true;

	right				= 10.f;
	left				= .01f;
	bottom				= .01f;
	top					= 10.f;
	fov					= 40.f;

	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, Z_NEAR, Z_FAR);
}

void Laborator5::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator5::Update(float deltaTimeSeconds)
{
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));

		// Attention! The RenderMesh function overrides the usual RenderMesh that we used until now
		// It uses the viewMatrix from Laborator::Camera instance and the local projectionMatrix
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
		RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.f, 2.5f, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90.f), glm::vec3(1.f, 1.f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, .5f, .3f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.f, 2.5f, 3.f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(180.f), glm::vec3(0.8f, 0, 0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(.8f, 1.f, .9f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	// Render the camera target. Useful for understanding where is the rotation point in Third-person camera movement
	if (renderCameraTarget)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}
}

void Laborator5::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Laborator5::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator5::OnInputUpdate(float deltaTime, int mods)
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

		if (window->KeyHold(GLFW_KEY_F))
		{
			fov += deltaTime * cameraSpeed;

			if (projectionType)
			{
				projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
			}
		}
		if (window->KeyHold(GLFW_KEY_G))
		{
			fov -= deltaTime * cameraSpeed;

			if (projectionType)
			{
				projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
			}
		}

		// BONUS: Keys to change the projection matrix in orthogonal mode (ew...)
		if (window->KeyHold(GLFW_KEY_UP))
		{
			bottom -= deltaTime;
			top += deltaTime;

			if (!projectionType)
			{
				projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
			}
		}
		if (window->KeyHold(GLFW_KEY_DOWN))
		{
			bottom += deltaTime;
			top -= deltaTime;

			if (!projectionType)
			{
				projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
			}
		}
		if (window->KeyHold(GLFW_KEY_LEFT))
		{
			left -= deltaTime;
			right += deltaTime;

			if (!projectionType)
			{
				projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
			}
		}
		if (window->KeyHold(GLFW_KEY_RIGHT))
		{
			left += deltaTime;
			right -= deltaTime;

			if (!projectionType)
			{
				projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
			}
		}
	}
}

void Laborator5::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}
	if (key == GLFW_KEY_O)
	{
		projectionType = false;
		projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
	}
	if (key == GLFW_KEY_P)
	{
		projectionType = true;
		projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
	}
}

void Laborator5::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0)
		{
			renderCameraTarget = false;
			// Rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// Use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL)
		{
			renderCameraTarget = true;
			// Rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// Use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}
	}
}

void Laborator5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator5::OnWindowResize(int width, int height)
{
}
