#pragma once

#include "PlaneRunner.h"

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

PlaneRunner::PlaneRunner() :
	zNear(0.01f), zFar(200.f),
	centreX(-4.5f), centreZ(0.f),
	propellerAcceleration(50.f),
	planeAcceleration(10.f),
	numClouds(10), numFuelCans(4), numObstacles(6)
{
}

PlaneRunner::~PlaneRunner()
{	
	/* Dealocate all memory */
	delete camera;
	delete plane;
	delete fuelBar;
	delete sea;
	delete revSea;
	delete heart;

	/* Dealocate static objects */
	Fuel::Destroy();
	Obstacle::Destroy();
	Cloud::Destroy();
}

void PlaneRunner::Init()
{
	srand((GLuint)time(NULL));

	plane			= new Aeroplane();
	fuelBar			= new FuelBar();
	sea				= new Sea(.35f, "Sea");
	revSea			= new Sea(.7f, "RevSea");
	heart			= new Heart();

	angle			= 0.f;
	propellerAngle	= 0.f;
	centreY			= 1.75f;
	planeSpeed		= 4.f;
	propellerSpeed	= 300.f;
	render			= GL_TRUE;
	numLives		= 3;
	cameraType		= 0;

	plane->GetBBoxOffsets(deltaXRight, deltaXLeft, deltaYUp, deltaYDown);

	/* The initial camera parameters */
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

	Obstacle::Init();
	Fuel::Init();
	Cloud::Init();

	/* Create the obstacles */
	for (GLushort i = 0; i != numObstacles; ++i)
	{
		obstacles.emplace_back();
	}

	/* Create the fuel cans */
	for (GLushort i = 0; i != numFuelCans; ++i)
	{
		fuelCans.emplace_back();
	}

	/* Create the clouds */
	for (GLushort i = 0; i != numClouds; ++i)
	{
		clouds.emplace_back();
	}

	/* The light that illuminates the sea */
	lightPosition = glm::vec3(-10.f, 11.5f, -20.f);
}

void PlaneRunner::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(1.f, .6f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
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

	/* Calculate bounding box coordinates */
	bBoxMaxX = centreX + deltaXRight * .3f;
	bBoxMinX = centreX + deltaXLeft * .3f;
	bBoxMaxY = centreY + deltaYUp * .3f;
	bBoxMinY = centreY + deltaYDown * .3f;

	/* Render all objects in the scene */
	RenderFuelCans(deltaTime);
	RenderObstacles(deltaTime);
	RenderClouds(deltaTime);
	RenderSea(deltaTime);
	RenderPlane(deltaTime);

	if (numLives > 0 && cameraType != 2)
	{
		RenderLives(deltaTime);
		RenderFuelBar(deltaTime);
	}
}

GLvoid PlaneRunner::MovePlane(GLfloat deltaTimeSeconds)
{
	if (numLives > 0 && fuelBar->HasFuel(deltaTimeSeconds))
	{
		/* Adjust the plane's angle to follow the mouse */
		angle = 5.f * atan(
			(mouseCrtX - centreX)
			/ (mouseCrtY - centreY + FLT_EPSILON)
		);

		centreY += planeSpeed * deltaTimeSeconds * sin(angle);
	} else if (centreY > -5.f)
	{
		/* If the plane is dead, make it spin */
		angle -= 10.f * deltaTimeSeconds;
		angle = angle > 360.f ? 0.f : angle;

		centreY -= 1.f * deltaTimeSeconds;
		numLives = 0;
	}

	/* Spin the propeller */
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
		plane->GetCockpit(offsetX, offsetY, offsetZ),
		offsetX, offsetY, offsetZ
	);

	if (cameraType == 2)
	{
		camera->Set(
			glm::vec3(cockpitMatrix[3][0], cockpitMatrix[3][1], cockpitMatrix[3][2]),
			glm::vec3(targetMatrix[3][0], targetMatrix[3][1], targetMatrix[3][2]),
			glm::vec3(0.f, 1.f, 0.f)
		);
	}

	/* Render the meshes that comprise the plane one by one */
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
	} else if (cameraType == 2 && !strcmp(planePart->GetMeshID(), "cockpit"))
	{
		/* Matrices for the camera in first person mode */
		cockpitMatrix = Transform3D::Translate(centreX, centreY, centreZ);
		cockpitMatrix *= Transform3D::RotateOZ(angle);
		cockpitMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		cockpitMatrix *= Transform3D::Translate(offsetX + .5f, offsetY, offsetZ);

		targetMatrix = Transform3D::Translate(centreX, centreY, centreZ);
		targetMatrix *= Transform3D::RotateOZ(angle);
		targetMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		targetMatrix *= Transform3D::Translate(offsetX + 10.f, offsetY, offsetZ);
	}

	if (!strcmp(planePart->GetMeshID(), "cockpit"))
	{
		/* The cockpit is transparent */
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		RenderMesh(planePart, plane->GetCockpitShader(), modelMatrix);
		
		glDisable(GL_BLEND);
	} else
	{
		RenderMesh(planePart, shaders["VertexColor"], modelMatrix);
	}

}

GLvoid PlaneRunner::RenderFuelCans(GLfloat deltaTimeSeconds)
{
	GLushort numCollisions = 0;
	std::vector<GLushort> collided;
	glm::mat4 model;

	/* Check each fuel can for a collision with the plane */
	for (GLushort i = 0; i != numFuelCans; ++i)
	{
		model = fuelCans[i].GetModelMatrix(deltaTimeSeconds);

		RenderTexturedMesh(
			Fuel::GetMesh(),
			Fuel::GetShader(),
			model,
			Fuel::GetTexture()
		);

		if (CheckCollision(model, fuelCans[i].GetRadius()))
		{
			fuelBar->AddFuel(fuelCans[i].GetFuelAmount());
			collided.push_back(i);

			++numCollisions;
		}
	}

	/* Erase and replace used cans */
	for (GLushort i = 0; i != numCollisions; ++i)
	{
		fuelCans.erase(fuelCans.begin() + collided[i]);
	}

	for (GLushort i = 0; i != numCollisions; ++i)
	{
		fuelCans.emplace_back();
	}
}

GLvoid PlaneRunner::RenderObstacles(GLfloat deltaTimeSeconds)
{
	GLushort numCollisions = 0;
	std::vector<GLushort> collided;
	glm::mat4 model;

	/* Check each obstacle for a collision with the plane */
	for (GLushort i = 0; i != numObstacles; ++i)
	{
		model = obstacles[i].GetModelMatrix(deltaTimeSeconds);

		RenderTexturedMesh(
			Obstacle::GetMesh(),
			Obstacle::GetShader(),
			model,
			Obstacle::GetTexture()
		);

		if (CheckCollision(model, obstacles[i].GetRadius()))
		{
			collided.push_back(i);
			++numCollisions;
			--numLives;
		}
	}

	/* Erase and replace the obstacles that were hit */
	for (GLushort i = 0; i != numCollisions; ++i)
	{
		obstacles.erase(obstacles.begin() + collided[i]);
	}

	for (GLushort i = 0; i != numCollisions; ++i)
	{
		obstacles.emplace_back();
	}
}

GLvoid PlaneRunner::RenderFuelBar(GLfloat deltaTimeSeconds)
{
	GLfloat scaleFactor;

	/* Render the background and the forground of the fuel bar */
	RenderMesh(
		fuelBar->GetBackground(),
		shaders["VertexColor"],
		Transform3D::Translate(-1.5f, 5.5f, 0.f)
	);

	Mesh* fuel = fuelBar->GetFuel(deltaTimeSeconds, scaleFactor);

	RenderMesh(
		fuel,
		shaders["VertexColor"],
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

	/* Render the clounds one by one, component by component */
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
}

GLvoid PlaneRunner::RenderLives(GLfloat deltaTimeSeconds)
{
	GLfloat posX	= -1.f;
	glm::mat4 aux	= heart->GetModelMatrix(deltaTimeSeconds);

	for (GLushort i = 0; i < numLives; ++i, posX += 1.f)
	{
		modelMatrix = Transform3D::Translate(posX, 4.5f, 0.f);
		modelMatrix *= Transform3D::Scale(.02f, .02f, .02f);
		modelMatrix *= aux;

		RenderTexturedMesh(
			heart->GetMesh(),
			heart->GetShader(),
			modelMatrix,
			heart->GetTexture()
		);
	}
}

GLvoid PlaneRunner::RenderSea(GLfloat deltaTimeSeconds)
{
	/* Render both seas */
	modelMatrix = sea->GetModelMatrix(deltaTimeSeconds);
	RenderMesh(sea->GetMesh(), sea->GetShader(), modelMatrix);

	modelMatrix = revSea->GetModelMatrix(deltaTimeSeconds);
	RenderMesh(revSea->GetMesh(), revSea->GetShader(), modelMatrix);
}

GLboolean PlaneRunner::CheckCollision(glm::mat4& model, GLfloat radius)
{
	/* https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection#Using_a_physics_engine */
	model			*= Transform3D::Translate(centreX, centreY, 0.f);
	model			*= Transform3D::RotateOZ(RADIANS(-angle));
	model			*= Transform3D::Translate(-centreX, -centreY, 0.f);

	glm::vec4 pos	= model * glm::vec4(0.f, 0.f, 0.f, 1.f);
	
	GLfloat posX	= pos[0];
	GLfloat posY	= pos[1];

	GLfloat projX	= MAX(bBoxMinX, MIN(posX, bBoxMaxX));
	GLfloat projY	= MAX(bBoxMinY, MIN(posY, bBoxMaxY));

	GLfloat dist	= (projX - posX) * (projX - posX) +
					  (projY - posY) * (projY - posY);

	return dist < radius * radius;
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
		glm::value_ptr(viewMatrix)
	);

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(
		shader->program,
		"Projection");
	glUniformMatrix4fv(
		loc_projection_matrix,
		1,
		GL_FALSE,
		glm::value_ptr(projectionMatrix)
	);

	// Activate texture location 0
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture ID
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	// Send texture uniform value
	glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(
		mesh->GetDrawMode(),
		static_cast<int>(mesh->indices.size()),
		GL_UNSIGNED_SHORT,
		0
	);
}

GLvoid PlaneRunner::RenderMesh(
	Mesh* mesh,
	Shader* shader,
	const glm::mat4& modelMatrix
)
{
	if (!mesh || !shader || !shader->program)
	{
		return;
	}

	shader->Use();

	glUniformMatrix4fv(
		shader->loc_view_matrix,
		1,
		GL_FALSE,
		glm::value_ptr(camera->GetViewMatrix())
	);
	glUniformMatrix4fv(
		shader->loc_projection_matrix,
		1,
		GL_FALSE,
		glm::value_ptr(projectionMatrix)
	);
	glUniformMatrix4fv(
		shader->loc_model_matrix,
		1,
		GL_FALSE,
		glm::value_ptr(modelMatrix)
	);
	
	if (!strcmp(mesh->GetMeshID(), "Sea") || !strcmp(mesh->GetMeshID(), "RevSea"))
	{
		glUniform1f(
			glGetUniformLocation(shader->program, "time"),
			(GLfloat)Engine::GetElapsedTime()
		);
		glUniform3fv(
			glGetUniformLocation(shader->program, "lightSea"),
			1,
			glm::value_ptr(lightPosition)
		);
		glUniform3fv(
			glGetUniformLocation(shader->program, "viewPos"),
			1,
			glm::value_ptr(camera->position)
		);
	}
	
	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void PlaneRunner::OnKeyPress(int key, int mods)
{
	/* Keyboard controls */
	if (key == GLFW_KEY_P)
	{
		render = !render;
	}

	if (key == GLFW_KEY_F)
	{
		cameraType = (cameraType + 1) % 3;

		switch (cameraType)
		{
		case 0:

			projectionMatrix = glm::perspective(
				RADIANS(60.f),
				window->props.aspectRatio,
				zNear,
				zFar
			);
			camera->Set(
				glm::vec3(0.f, 3.f, 10.f),
				glm::vec3(0.f, 1.f, 0.f),
				glm::vec3(0.f, 1.f, 0.f)
			);

			break;
		case 1:
			projectionMatrix = glm::ortho(-8.0f, 8.0f, -3.5f, 5.f, zNear, zFar);
			camera->Set(
				glm::vec3(0.f, 2.f, 10.f),
				glm::vec3(0.f, 1.f, 0.f),
				glm::vec3(0.f, 1.f, 0.f)
			);

			break;

		default:
			projectionMatrix = glm::perspective(
				RADIANS(90.f),
				window->props.aspectRatio,
				zNear,
				zFar
			);

			numLives = 1;

			break;
		}
	}
}

void PlaneRunner::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	mouseCrtX = (GLfloat)mouseX;
	mouseCrtY = (GLfloat)mouseY;
}