#include "Worms.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Worms::Worms()
{
}

Worms::~Worms()
{
	delete terrain;
}

void Worms::Init()
{
	terrain = new Terrain();
}

void Worms::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Worms::Update(float deltaTimeSeconds)
{
	modelMatrix = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, 0.f));

	/* Render the terrain */
	{
		RenderMesh(
			terrain->GetMesh(),
			shaders["VertexColor"],
			modelMatrix,
			terrain->GetTexture()
		);
	}
}

void Worms::FrameEnd()
{
	DrawCoordinatSystem();
}

GLvoid Worms::RenderMesh(
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
	GLint locModelMatrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(locModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(
		loc_view_matrix,
		1,
		GL_FALSE,
		glm::value_ptr(viewMatrix)
	);

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	GLint locProjectionMatrix = glGetUniformLocation(
		shader->program,
		"Projection"
	);
	glUniformMatrix4fv(
		locProjectionMatrix,
		1,
		GL_FALSE,
		glm::value_ptr(projectionMatrix)
	);

	// GLint locHeightMap = glGetUniformLocation(shader->program, "heightMap");
	//glUniform

	// Activate texture location 0
	//glActiveTexture(GL_TEXTURE0);

	//// Bind the texture1 ID
	//glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	//// Send texture uniform value
	//glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(
		mesh->GetDrawMode(),
		static_cast<int>(mesh->indices.size()),
		GL_UNSIGNED_SHORT,
		0
	);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Worms::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	}
}

void Worms::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Worms::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Worms::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Worms::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Worms::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Worms::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Worms::OnWindowResize(int width, int height)
{
}
