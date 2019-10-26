#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"


Tema1::Tema1():
	fallAngleSpeed(50.f),
	riseAngleSpeed(100.f),
	gravity(400.f),
	liftForce(300.f)
{
}

Tema1::~Tema1()
{
	delete bird;
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	bird				= new Bird();
	trueScore			= 0.f;
	shownScore			= 0;
	
	angle				= 0.f;
	fall				= true;

	centreX				= 200.f;
	centreY				= resolution.y / 2.f + 200.f;
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	GLfloat offsetX, offsetY;
	Mesh* bodyPart;
	glm::ivec2 resolution = window->GetResolution();

	bird->FlapWing(deltaTimeSeconds);
	speed -= gravity * deltaTimeSeconds;
	centreY += speed * deltaTimeSeconds
		- gravity * deltaTimeSeconds * deltaTimeSeconds / 2.f;
	
	/* Transformations that will be applied to the bird, one part at a time */
	CalculateMovementMatrix();
	CalculateBirdAngle(deltaTimeSeconds);

	/* Reneder all the bird parts one by one */
	/* Render the wing */
	{
		bodyPart = bird->getWingMesh(offsetX, offsetY);
		RenderBodyPart(bodyPart, offsetX, offsetY);
	}

	/* Render the beak */
	{
		bodyPart = bird->getBeakMesh(offsetX, offsetY);
		RenderBodyPart(bodyPart, offsetX, offsetY);
	}

	/* Render the eye */
	{
		bodyPart = bird->getEyeMesh(offsetX, offsetY);
		RenderBodyPart(bodyPart, offsetX, offsetY);
	}

	/* Render the head */
	{
		bodyPart = bird->getHeadMesh(offsetX, offsetY);
		RenderBodyPart(bodyPart, offsetX, offsetY);
	}

	/* Render the body */
	{
		bodyPart = bird->getBodyMesh(offsetX, offsetY);
		RenderBodyPart(bodyPart, offsetX, offsetY);
	}

	/* Render the tail */
	{
		bodyPart = bird->getTailMesh(offsetX, offsetY);
		RenderBodyPart(bodyPart, offsetX, offsetY);
	}


	/* Print the score */
	trueScore += deltaTimeSeconds * 2.f;

	if ((GLint)trueScore > shownScore)
	{
		shownScore = (GLint)trueScore;
		cout << "Score: " << shownScore << "\n\n";
	}
}

void Tema1::FrameEnd()
{
}

void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		// TODO: sari, fa, sari
		fall = false;
		speed = liftForce;
	}
}

void Tema1::RenderBodyPart(Mesh* bodyPart, GLfloat offsetX, GLfloat offsetY)
{
	glm::mat3 offsetMatrix = modelMatrix;
	offsetMatrix *= Transform2D::Rotate(RADIANS(angle));
	offsetMatrix *= Transform2D::Translate(offsetX, offsetY);

	RenderMesh2D(bodyPart, shaders["VertexColor"], offsetMatrix);
}

void Tema1::CalculateMovementMatrix()
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(centreX, centreY);
	// TODO: misca cioara
}

void Tema1::CalculateBirdAngle(float deltaTimeSeconds)
{
	if (fall)
	{
		angle -= deltaTimeSeconds * fallAngleSpeed;
		
		if (angle <= -90.f)
		{
			angle = -90.f;
		}
	} else
	{
		angle += deltaTimeSeconds * riseAngleSpeed;

		if (angle >= 30.f)
		{
			fall = true;
		}
	}
}