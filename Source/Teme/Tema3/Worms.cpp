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
	delete projectile;
}

void Worms::Init()
{
	{
		terrain		= new Terrain();
		projectile	= new Projectile();
	}

	/* Lighting properties */
	{
		lightPosition1		= glm::vec3(5.f, 2.f, 5.f);
		lightPosition2		= glm::vec3(2.f, 2.f, 2.f);
		lightDirection		= glm::vec3(0.f, -1.f, 0.f);
		materialShininess	= 30;
		materialKd			= .5f;
		materialKs			= .5f;
		cutOffAngle			= 30.f;
	}
}

void Worms::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Worms::Update(float deltaTimeSeconds)
{
	modelMatrix = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, 0.f));

	/* Render the terrain */
	RenderMesh(
		terrain->GetMesh(),
		terrain->GetShader(),
		modelMatrix,
		terrain->GetTexture()
	);

	/* Render the projectile if that is the case */
	if (projectile->HasBeenFired())
	{
		projectile->MoveProjectile(deltaTimeSeconds);
		projectile->GetPosition(posX, posY, posZ);

		if (posY >= 0.f)
		{
			GLfloat scale	= projectile->GetRadius() * 2.f;
			modelMatrix		= glm::translate(
				glm::mat4(1.f),
				glm::vec3(posX, posY, posZ)
			);
			modelMatrix		= glm::scale(
				modelMatrix,
				glm::vec3(scale, scale, scale)
			);

			RenderMesh(
				projectile->GetMesh(),
				projectile->GetShader(),
				modelMatrix,
				projectile->GetTexture()
			);
		} else
		{
			projectile->NotFired();
		}
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
	if (!mesh || !shader || !shader->GetProgramID() || !texture)
	{
		return;
	}

	/* Render an object using the specified shader and the specified position */
	glUseProgram(shader->program);

	/* Bind model matrix */
	GLint locModelMatrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(locModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	/* Bind view matrix */
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	GLint locViewMatrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(
		locViewMatrix,
		1,
		GL_FALSE,
		glm::value_ptr(viewMatrix)
	);

	/* Bind projection matrix */
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

	/* If the mesh is the terrain, then also provide the heightmap */
	if (!strcmp(mesh->GetMeshID(), "TerrainMesh"))
	{
		/* Set the light parameters */
		GLint locLightPos = glGetUniformLocation(shader->program, "lightPosition1");
		glUniform3f(locLightPos, lightPosition1.x, lightPosition1.y, lightPosition1.z);

		locLightPos = glGetUniformLocation(shader->program, "lightPosition2");
		glUniform3f(locLightPos, lightPosition2.x, lightPosition2.y, lightPosition2.z);

		GLint locLightDir = glGetUniformLocation(shader->program, "lightDirection");
		glUniform3f(locLightDir, lightDirection.x, lightDirection.y, lightDirection.z);

		GLint locCutOffAngle = glGetUniformLocation(shader->program, "cutOffAngle");
		glUniform1f(locCutOffAngle, cutOffAngle);

		/* Set eye position (camera position) uniform */
		glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
		GLint locEyePos = glGetUniformLocation(shader->program, "eyePosition");
		glUniform3f(locEyePos, eyePosition.x, eyePosition.y, eyePosition.z);

		/* Set material property uniforms (shininess, kd, ks) */
		GLint locShininess = glGetUniformLocation(shader->program, "materialShininess");
		glUniform1i(locShininess, materialShininess);

		GLint locMaterialKD = glGetUniformLocation(shader->program, "materialKd");
		glUniform1f(locMaterialKD, materialKd);

		GLint locMaterialKS = glGetUniformLocation(shader->program, "materialKs");
		glUniform1f(locMaterialKS, materialKs);

		/* Activate texture location 1 */
		glActiveTexture(GL_TEXTURE1);

		/* Bind the texture ID */
		glBindTexture(
			GL_TEXTURE_2D,
			terrain->GetHeightTexture(posX, posY, posZ)->GetTextureID()
		);

		/* Send texture uniform value */
		glUniform1i(glGetUniformLocation(shader->program, "heightTexture"), 1);

		/* Send the height and the width of the terrain */
		GLint locHeight = glGetUniformLocation(shader->program, "terrainHeight");
		glUniform1i(locHeight, terrain->GetHeightMapHeight());

		GLint locWidth = glGetUniformLocation(shader->program, "terrainWidth");
		glUniform1i(locWidth, terrain->GetHeightMapWidth());
	}

	/* Activate texture location 0 */
	glActiveTexture(GL_TEXTURE0);

	/* Bind the texture ID */
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	/* Send texture uniform value */
	glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);

	/* Draw the object */
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
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !projectile->HasBeenFired())
	{
		projectile->Fire(
			2.5f,
			.5f,
			2.5f,
			RADIANS(90.f),
			RADIANS(0.f)
		);
	}
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
