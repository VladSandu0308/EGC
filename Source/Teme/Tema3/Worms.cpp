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
	delete camera;
	Player::Destroy();
}

void Worms::Init()
{
	/* Lighting properties */
	{
		lightPosition1		= glm::vec3(5.45f, 2.f, 5.56f);
		lightPosition2		= glm::vec3(1.54f, 2.f, 1.85f);
		lightDirection		= glm::vec3(0.f, -1.f, 0.f);
		materialShininess	= 30;
		materialKd			= .5f;
		materialKs			= .5f;
		cutOffAngle			= 30.f;
	}

	Player::Init();

	{
		crtPlayer = 0;
		players.emplace_back(1.54f, .48f, 1.85f, 90.f);
		players.emplace_back(5.45f, .39f, 5.56f, 90.f);
	}

	{
		projectile	= new Projectile();
		terrain		= new Terrain();
		camera		= new WormsGame::Camera();
		camera->Set(
			glm::vec3(1.3f, .6f, 1.5f),
			glm::vec3(1.54f, .48f, 1.85f),
			glm::vec3(0.f, 1.f, 0.f)
		);

		projectionMatrix = glm::perspective(
			RADIANS(60.f),
			window->props.aspectRatio,
			.01f,
			200.f
		);
	}

	cameraTime = 0.f;
}

void Worms::FrameStart()
{
	/* Clears the color buffer (using the previously set color) and depth buffer */
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Sets the screen area where to draw */
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Worms::Update(float deltaTimeSeconds)
{
	/* Render the projectile if that is the case */
	if (projectile->HasBeenFired())
	{
		projectile->MoveProjectile(deltaTimeSeconds);
		projectile->GetPosition(posX, posY, posZ);

		/* The area of interest is y >= 0 */
		if (posY >= 0.f)
		{
			RenderMesh(
				projectile->GetMesh(),
				projectile->GetShader(),
				projectile->GetModelMatrix(),
				projectile->GetTexture()
			);

			/* Set the camera to follow the projectile */
			if (crtPlayer)
			{
				camera->Set(
					glm::vec3(posX + .3f, posY + .5f, posZ + .5f),
					glm::vec3(posX, posY, posZ),
					glm::vec3(0.f, 1.f, 0.f)
				);
			} else
			{
				camera->Set(
					glm::vec3(posX - .3f, posY + .5f, posZ - .5f),
					glm::vec3(posX, posY, posZ),
					glm::vec3(0.f, 1.f, 0.f)
				);
			}

			/* Dig a hole in the ground where there is a collision */
			if (terrain->CheckCollision(
					posX,
					posY,
					posZ,
					projectile->GetRadius())
				)
			{
				terrain->DeformTerrain(
					posX,
					posY,
					posZ,
					projectile->GetBlastRadius()
				);

				projectile->NotFired();

				players[crtPlayer ^ 1].CheckCollision(
					posX,
					posY,
					posZ,
					projectile->GetRadius()
				);

				/* Change players only if the other is alive */
				if (players[crtPlayer ^ 1].IsAlive())
				{
					crtPlayer ^= 1;
				}				
			}
		} else
		{
			projectile->NotFired();
			crtPlayer ^= 1;
		}
	} else
	{
		/* After 0.5 seconds, change the camera to the other player */
		if (cameraTime > .5f)
		{
			if (crtPlayer)
			{
				camera->Set(
					glm::vec3(5.75f, .55f, 5.85f),
					glm::vec3(5.45f, .39f, 5.56f),
					glm::vec3(0.f, 1.f, 0.f)
				);
			} else
			{
				camera->Set(
					glm::vec3(1.3f, .7f, 1.5f),
					glm::vec3(1.54f, .48f, 1.85f),
					glm::vec3(0.f, 1.f, 0.f)
				);
			}
		} else
		{
			cameraTime += deltaTimeSeconds;
		}
	}

	/* Render the terrain */
	RenderMesh(
		terrain->GetMesh(),
		terrain->GetShader(),
		modelMatrix,
		terrain->GetTexture()
	);
	
	/* Render the players */
	{
		for (Player& player : players)
		{
			if (player.IsAlive())
			{
				RenderMesh(
					player.GetBazookaMesh(),
					player.GetShader(),
					player.GetBazookaModelMatrix(),
					player.GetBazookaTexture()
				);
				RenderMesh(
					player.GetBearMesh(),
					player.GetShader(),
					player.GetBearModelMatrix(),
					player.GetBearTexture()
				);
			}
		}
	}
}

void Worms::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
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
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	GLint locViewMatrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(
		locViewMatrix,
		1,
		GL_FALSE,
		glm::value_ptr(viewMatrix)
	);

	/* Bind projection matrix */
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
		glm::vec3 eyePosition = camera->position;
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

/**
*	Documentation for the input functions can be found in:
*	"/Source/Core/Window/InputController.h" or
*	https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h
*/

void Worms::OnInputUpdate(float deltaTime, int mods)
{
	GLfloat deltaTimeYaw = 0.f, deltaTimePitch = 0.f;

	if (window->KeyHold(GLFW_KEY_UP))
	{
		deltaTimePitch += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_DOWN))
	{
		deltaTimePitch -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_LEFT))
	{
		deltaTimeYaw += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_RIGHT))
	{
		deltaTimeYaw -= deltaTime;
	}

	players[crtPlayer].UpdateAngles(deltaTimeYaw, deltaTimePitch);
}

void Worms::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	/* Mouse move events */
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0)
		{
			/*
			* Rotate the camera in First-person mode around OX and OY using
			* deltaX and deltaY.
			* Use the sensitivity variables for setting up the rotation speed
			*/
			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}
	}
}

void Worms::OnKeyPress(int key, int mods)
{
	/* Fire the bazooka with SPACE */
	if (key == GLFW_KEY_SPACE && !projectile->HasBeenFired())
	{
		players[crtPlayer].GetProjectileStartPos(posX, posY, posZ);
		PlaySound(TEXT("rocket.wav"), NULL, SND_FILENAME | SND_ASYNC);
		projectile->Fire(
			posX,
			posY,
			posZ,
			RADIANS(players[crtPlayer].GetAnglePitch()),
			RADIANS(players[crtPlayer].GetAngleYaw())
		);
		cameraTime = 0.f;
	}
}

void Worms::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	/* Fire the bazooka with the left mouse button */
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !projectile->HasBeenFired())
	{
		players[crtPlayer].GetProjectileStartPos(posX, posY, posZ);
		PlaySound(TEXT("rocket.wav"), NULL, SND_FILENAME | SND_ASYNC);
		projectile->Fire(
			posX,
			posY,
			posZ,
			RADIANS(players[crtPlayer].GetAnglePitch()),
			RADIANS(players[crtPlayer].GetAngleYaw())
		);
		cameraTime = 0.f;
	}
}
