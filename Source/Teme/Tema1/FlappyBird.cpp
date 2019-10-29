#include "FlappyBird.h"

#include <Core/Engine.h>
#include "Transform2D.h"


FlappyBird::FlappyBird() :
	fallAngleSpeed(100.f),
	riseAngleSpeed(200.f),
	gravity(1200.f),
	liftForce(300.f),
	totalNumObstacles(20),
	numObstacles(4),
	obstacleWidth(80.f),
	obstacleDistance(325.f),
	obstacleStart(955.f),
	numPoints(50),
	scaleSpeed(300.f)
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
	camera->SetOrthographic(
		0,
		(GLfloat)resolution.x,
		0,
		(GLfloat)resolution.y,
		0.01f,
		400);
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
	centreY			= (GLfloat)resolution.y * 1.5f;

	obstacleSpeed	= 200.f;
	speed			= liftForce;

	bird->getHeadRadius(birdHeadRadius);
	bird->getBodyRadii(birdBodyRadiusX, birdBodyRadiusY);
	birdHitBox			= bird->getHitBox();
	birdHitBoxRadius	= bird->getHitBoxRadius();

	/* Use the Mersenne Twister to generate random obstacle colours */
	std::random_device rd;
	engine.seed(rd());
	floatDist = std::uniform_real_distribution<GLfloat>(0.0, 1.0);
	shortDist = std::uniform_int_distribution<GLushort>(0, 255);

	GLfloat r, g, b;

	for (GLushort i = 0; i < totalNumObstacles; ++i)
	{
		r = floatDist(engine);
		g = floatDist(engine);
		b = floatDist(engine);

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
		pos							= shortDist(engine) % totalNumObstacles;
		
		usedObstacles[i].obstacle	= &allObstacles[pos];
		usedObstacles[i].posX		= posX;
		usedObstacles[i].scale		= 10.f / (shortDist(engine) % 30 + 20);;

		if (!(shortDist(engine) % 5))
		{
			usedObstacles[i].isVariable = true;
			usedObstacles[i].scaleAngle = 0.f;
		}
		else
		{
			usedObstacles[i].isVariable = false;
			usedObstacles[i].scaleAngle = 90.f;
		}
	}
}

GLvoid FlappyBird::FrameStart()
{
	/* Clear the color buffer (using the previously set color) and depth buffer */
	glClearColor(0.5725f, 0.718f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Set the screen area where to draw */
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

GLvoid FlappyBird::Update(GLfloat deltaTimeSeconds)
{
	GLfloat offsetX, offsetY;
	Mesh* bodyPart;
	glm::ivec2 resolution = window->GetResolution();

	if (!collision)
	{
		/* Make the bird fly */
		bird->FlapWing(deltaTimeSeconds);

		/* Transformations that will be applied to each part of the bird */
		CalculateBirdMovement(deltaTimeSeconds);
		CalculateBirdAngle(deltaTimeSeconds);

		/* Print the score */
		trueScore += deltaTimeSeconds * 2.f * obstacleSpeed / 200.f;
		obstacleSpeed += deltaTimeSeconds * 30.f;

		if ((GLint)trueScore > shownScore)
		{
			shownScore = (GLint)trueScore;
			std::cout << "Score: " << shownScore << "\n\n";
		}
	}

	/* Render the obstacles */
	RenderObstacles(deltaTimeSeconds);

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

	/* Render the hit box */
	{
		bodyPart = bird->getHitBoxMesh(offsetX, offsetX);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		RenderBodyPart(bodyPart, offsetX, offsetY);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

GLvoid FlappyBird::FrameEnd()
{
}

GLvoid FlappyBird::OnKeyPress(GLint key, GLint mods)
{
	if (key == GLFW_KEY_SPACE && !collision)
	{
		//PlaySound(TEXT("crow_caw.wav"), NULL, SND_FILENAME | SND_ASYNC);

		fall = false;
		speed = liftForce;
	}
}

GLvoid FlappyBird::CalculateBirdAngle(GLfloat deltaTimeSeconds)
{
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
}

GLvoid FlappyBird::RenderBodyPart(
	Mesh* bodyPart,
	GLfloat offsetX,
	GLfloat offsetY)
{
	modelMatrix = Transform2D::Translate(centreX, centreY);
	modelMatrix *= Transform2D::Rotate(RADIANS(angle));
	modelMatrix *= Transform2D::Translate(offsetX, offsetY);

	RenderMesh2D(bodyPart, shaders["VertexColor"], modelMatrix);
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
		if (!collision)
		{
			obs.posX -= deltaTimeSeconds * obstacleSpeed;

			if (obs.isVariable)
			{
				obs.scaleAngle += deltaTimeSeconds * scaleSpeed;

				if (obs.scaleAngle >= 180.f)
				{
					obs.scaleAngle = 0.f;
				}
			}
		}

		if (!isObstacleInMap(obs))
		{
			GLushort pos		= shortDist(engine) % totalNumObstacles;

			obs.obstacle	= &allObstacles[pos];
			obs.posX		= (GLfloat)resolution.x;
			obs.scale		= 10.f / (shortDist(engine) % 31 + 20);

			if (!(shortDist(engine) % 5))
			{
				obs.isVariable = true;
				obs.scaleAngle = 0.f;
			} else
			{
				obs.isVariable = false;
				obs.scaleAngle = 90.f;
			}
		} else
		{
			modelMatrix = Transform2D::Translate(obs.posX, 0.f);
			modelMatrix *= Transform2D::Scale(
				1.f,
				obs.scale * sin(RADIANS(obs.scaleAngle)));
			RenderMesh2D(
				obs.obstacle->getMesh(),
				shaders["VertexColor"],
				modelMatrix);
			
			modelMatrix = Transform2D::Translate(
				obs.posX + obstacleWidth,
				(GLfloat)resolution.y);
			modelMatrix *= Transform2D::Rotate(RADIANS(180.f));
			modelMatrix *= Transform2D::Scale(
				1.f,
				(0.6f - obs.scale) * sin(RADIANS(obs.scaleAngle)));
			RenderMesh2D(
				obs.obstacle->getMesh(),
				shaders["VertexColor"],
				modelMatrix);

			if (centreX + birdHitBoxRadius >= obs.posX
				&& centreX - birdHitBoxRadius <= obs.posX + obstacleWidth)
			{
				if (!collision)
				{
					collision = checkBirdCollision(
						obs.posX,
						0.f,
						resolution.y * obs.scale * sin(RADIANS(obs.scaleAngle)));
				}
				if (!collision)
				{
					collision = checkBirdCollision(
						obs.posX,
						resolution.y * (1.f - (0.6f - obs.scale) * sin(RADIANS(obs.scaleAngle))),
						(GLfloat)resolution.y);
				}
			}			
		}
	}
}

GLboolean FlappyBird::checkBirdCollision(
	GLfloat lowX,
	GLfloat lowY,
	GLfloat highY)
{
	GLfloat birdX, birdY;

	for (auto& point : birdHitBox)
	{
		birdX = centreX + point.coordX;
		birdY = centreY + point.coordY;

		if (birdX <= lowX + obstacleWidth && birdX >= lowX
			&& birdY <= highY && birdY >= lowY)
		{
			return true;
		}
	}

	return false;
}