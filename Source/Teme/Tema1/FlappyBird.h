#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include <ctime>
#include <random>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

#include "Obstacle.h"
#include "Bird.h"

#pragma comment(lib, "winmm.lib")

#define coordX first
#define coordY second

class FlappyBird : public SimpleScene
{
public:
	FlappyBird();
	~FlappyBird();

	GLvoid Init() override;

private:
	struct ObstaclePos
	{
		GLboolean isVariable;
		GLfloat scaleAngle;
		GLfloat posX;
		GLfloat scale;
		Obstacle* obstacle;
	};

	GLvoid FrameStart() override;
	GLvoid Update(GLfloat deltaTimeSeconds) override;
	GLvoid FrameEnd() override;

	GLvoid OnKeyPress(GLint key, GLint mods) override;

	GLvoid RenderBodyPart(Mesh* bodyPart, GLfloat offsetX, GLfloat offsetY);
	GLvoid RenderObstacles(GLfloat deltaTimeSeconds);
	inline GLboolean isObstacleInMap(ObstaclePos& obs);

	GLvoid CalculateBirdMovement(GLfloat deltaTimeSeconds);
	GLvoid CalculateBirdAngle(GLfloat deltaTimeSeconds);

	GLboolean checkBirdCollision(GLfloat lowX, GLfloat lowY, GLfloat highY);

protected:
	const GLfloat numPoints;

	const GLfloat fallAngleSpeed;
	const GLfloat riseAngleSpeed;
	
	const GLfloat gravity;
	const GLfloat liftForce;
	
	const GLushort numObstacles;
	const GLushort totalNumObstacles;
	const GLfloat obstacleWidth;
	const GLfloat obstacleDistance;
	const GLfloat obstacleStart;
	const GLfloat scaleSpeed;
	GLfloat obstacleSpeed;

	GLfloat birdHeadRadius;
	GLfloat birdBodyRadiusX;
	GLfloat birdBodyRadiusY;

	glm::mat3 modelMatrix;

	GLfloat centreX, centreY;
	GLboolean fall;
	GLboolean collision;
	GLfloat speed;
	GLfloat angle;

	GLfloat trueScore;
	GLint shownScore;

	Bird* bird;
	GLfloat birdHitBoxRadius;
	std::vector<std::pair<GLfloat, GLfloat>> birdHitBox;

	std::vector<Obstacle> allObstacles;
	std::vector<ObstaclePos> usedObstacles;

	std::mt19937 engine;
	std::uniform_real_distribution<GLfloat> floatDist;
	std::uniform_int_distribution<GLushort> shortDist;
};
