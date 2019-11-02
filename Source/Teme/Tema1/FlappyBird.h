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

/* To make std::pair more expressive */
#define coordX first
#define coordY second

class FlappyBird : public SimpleScene
{
public:
	FlappyBird();
	~FlappyBird();

	GLvoid Init() override;

private:
	/* Will contain information regarding each obstacle */
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

	/* Renders the bird mesh by mesh */
	GLvoid RenderBird(GLfloat deltaTimeSeconds);

	/**
	* Creates a given part of the bird and places it at its corresponding
	* offsets
	*/
	GLvoid RenderBodyPart(
		Mesh* bodyPart,
		GLfloat offsetX,
		GLfloat offsetY,
		GLfloat deltaTimeSeconds);

	/* Renders all obstacles and checks for collisions */
	GLvoid RenderObstacles(GLfloat deltaTimeSeconds);

	/**
	* Checks if an obstacle is still visible in order to decide if it should
	* be rendered
	*/
	inline GLboolean IsObstacleInMap(ObstaclePos& obs);

	/**
	* Uses the equation of motion in order to update the coordinates of the
	* bird's centre.
	* Also calculates a new scale factor for the wing
	*/
	GLvoid CalculateBirdMovement(GLfloat deltaTimeSeconds);

	/* Calculates the bird's inclination */
	GLvoid CalculateBirdAngle(GLfloat deltaTimeSeconds);

	/* Rotates the bird's ordinary hitbox to reflect its orientation */
	GLvoid CalculateBirdHitBox();

	/**
	* Checks if the bird is colliding with an object identified by its
	* corners
	*/
	GLboolean CheckBirdCollision(GLfloat lowX, GLfloat lowY, GLfloat highY);

	/* Checks if the bird is still inside the viewport */
	GLboolean CheckBirdInMap();

protected:
	GLboolean finalScore;
	GLboolean canRender;
	GLboolean sound;

	const GLfloat numPoints;

	const GLfloat fallAngleSpeed;
	const GLfloat riseAngleSpeed;
	GLfloat birdWingScaleSpeed;
	
	const GLfloat gravity;
	const GLfloat liftForce;
	
	const GLushort numObstacles;
	const GLushort totalNumObstacles;
	const GLfloat obstacleWidth;
	const GLfloat obstacleDistance;
	const GLfloat obstacleStart;
	const GLfloat scaleSpeed;
	const GLfloat wingScaleSpeeddAcc;
	GLfloat sign;
	GLfloat obstacleSpeed;

	GLfloat birdHeadRadius;
	GLfloat birdBodyRadiusX;
	GLfloat birdBodyRadiusY;
	GLfloat birdWingScale;

	GLfloat centreX, centreY;
	GLboolean fall;
	GLboolean collision;
	GLfloat speed;
	GLfloat angle;

	GLfloat trueScore;
	GLint shownScore;

	glm::mat3 modelMatrix;

	Bird* bird;
	GLfloat birdHitBoxRadius;
	std::vector<std::pair<GLfloat, GLfloat>> birdHitBox;
	GLboolean renderHitBox;

	std::vector<Obstacle> allObstacles;
	std::vector<ObstaclePos> usedObstacles;

	const std::string texturesLoc;
	const std::string shadersLoc;
	Texture2D* obstacleTexture;
};
