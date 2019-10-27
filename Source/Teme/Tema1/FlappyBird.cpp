#include "FlappyBird.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"


FlappyBird::FlappyBird() :
	fallAngleSpeed(50.f),
	riseAngleSpeed(200.f),
	gravity(700.f),
	liftForce(300.f),
	totalNumObstacles(20),
	numObstacles(4),
	obstacleWidth(80.f),
	obstacleDistance(325.f),
	obstacleStart(630.f)
{
}

FlappyBird::~FlappyBird()
{
	delete bird;
}

GLvoid FlappyBird::Init()
{
	srand((unsigned int)time(NULL));

	glm::ivec2 resolution = window->GetResolution();

	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (GLfloat)resolution.x, 0, (GLfloat)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	bird			= new Bird();
	trueScore		= 0.f;
	shownScore		= 0;
	
	angle			= 0.f;
	fall			= true;
	collision		= false;

	centreX			= 200.f;
	centreY			= (GLfloat)resolution.y;

	obstacleSpeed = 200.f;

	GLfloat r, g, b;

	for (GLushort i = 0; i < totalNumObstacles; ++i)
	{
		r = (rand() % 255) / 255.f;
		g = (rand() % 255) / 255.f;
		b = (rand() % 255) / 255.f;

		allObstacles.emplace_back(
			obstacleWidth,
			(GLfloat)resolution.y,
			r,
			g,
			b);
	}

	GLushort pos;
	GLfloat scaleFactor;
	GLfloat posX = obstacleStart;

	usedObstacles.resize(numObstacles);

	for (GLushort i = 0; i < numObstacles; ++i, posX += obstacleDistance)
	{
		pos							= rand() % totalNumObstacles;
		scaleFactor					= 10.f / (rand() % 30 + 20);
		
		usedObstacles[i].obstacle	= &allObstacles[pos];
		usedObstacles[i].posX		= posX;
		usedObstacles[i].scale		= scaleFactor;
	}
}

GLvoid FlappyBird::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

GLvoid FlappyBird::Update(GLfloat deltaTimeSeconds)
{
	GLfloat offsetX, offsetY;
	Mesh* bodyPart;
	glm::ivec2 resolution = window->GetResolution();

	/* Make the bird fly */
	bird->FlapWing(deltaTimeSeconds);

	/* Render the obstacles */
	RenderObstacles(deltaTimeSeconds);
	
	/* Transformations that will be applied to the bird, one part at a time */
	CalculateBirdMovement(deltaTimeSeconds);
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

	if (!collision)
	{
		/* Print the score */
		trueScore += deltaTimeSeconds * 2.f * obstacleSpeed / 200.f;
		obstacleSpeed += deltaTimeSeconds * 30.f;

		if ((GLint)trueScore > shownScore)
		{
			shownScore = (GLint)trueScore;
			std::cout << "Score: " << shownScore << "\n\n";
		}
	}	
}

GLvoid FlappyBird::FrameEnd()
{
}

GLvoid FlappyBird::OnKeyPress(GLint key, GLint mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		fall = false;
		speed = liftForce;
	}
}

GLvoid FlappyBird::CalculateBirdAngle(GLfloat deltaTimeSeconds)
{
	if (collision)
	{
		return;
	}

	if (fall)
	{
		angle -= deltaTimeSeconds * fallAngleSpeed;

		if (angle <= -90.f)
		{
			angle = -90.f;
		}
	}
	else
	{
		angle += deltaTimeSeconds * riseAngleSpeed;

		if (angle >= 30.f)
		{
			fall = true;
		}
	}
}

GLvoid FlappyBird::CalculateBirdMovement(GLfloat deltaTimeSeconds)
{
	speed -= gravity * deltaTimeSeconds;
	centreY +=
		speed * deltaTimeSeconds
		- gravity * deltaTimeSeconds * deltaTimeSeconds / 2.f;

	modelMatrix = Transform2D::Translate(centreX, centreY);
}

GLvoid FlappyBird::RenderBodyPart(Mesh* bodyPart, GLfloat offsetX, GLfloat offsetY)
{
	birdPartMatrix = modelMatrix;
	birdPartMatrix *= Transform2D::Rotate(RADIANS(angle));
	birdPartMatrix *= Transform2D::Translate(offsetX, offsetY);

	RenderMesh2D(bodyPart, shaders["VertexColor"], birdPartMatrix);
}

inline GLboolean FlappyBird::isObstacleInMap(ObstaclePos& obs)
{
	return obs.posX + obstacleWidth >= 0.f;
}

GLvoid FlappyBird::RenderObstacles(GLfloat deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	for (ObstaclePos& obs : usedObstacles)
	{
		obs.posX -= deltaTimeSeconds * obstacleSpeed;

		if (!isObstacleInMap(obs))
		{
			GLushort pos		= rand() % totalNumObstacles;
			GLfloat scaleFactor = 10.f / (rand() % 31 + 20);

			obs.obstacle	= &allObstacles[pos];
			obs.posX		= (GLfloat)resolution.x;
			obs.scale		= scaleFactor;
		} else
		{
			modelMatrix = Transform2D::Translate(obs.posX, 0.f);
			modelMatrix *= Transform2D::Scale(1.f, obs.scale);
			RenderMesh2D(
				obs.obstacle->getMesh(),
				shaders["VertexColor"],
				modelMatrix);
			
			modelMatrix = Transform2D::Translate(
				obs.posX + obstacleWidth,
				(GLfloat)resolution.y);
			modelMatrix *= Transform2D::Rotate(RADIANS(180.f));
			modelMatrix *= Transform2D::Scale(1.f, 0.6f - obs.scale);
			RenderMesh2D(
				obs.obstacle->getMesh(),
				shaders["VertexColor"],
				modelMatrix);
		}
	}
}
