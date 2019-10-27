#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Bird.h"

class FlappyBird : public SimpleScene
{
public:
	FlappyBird();
	~FlappyBird();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnKeyPress(int key, int mods) override;

	void RenderBodyPart(Mesh* bodyPart, GLfloat offsetX, GLfloat offsetY);
	void CalculateMovementMatrix();
	void CalculateBirdAngle(float deltaTimeSeconds);

protected:
	const GLfloat fallAngleSpeed;
	const GLfloat riseAngleSpeed;
	const GLfloat gravity;
	const GLfloat liftForce;

	glm::mat3 modelMatrix, offsetMatrix;
	GLfloat centreX, centreY;
	GLboolean fall;
	GLfloat speed;

	GLfloat trueScore;
	GLint shownScore;

	Bird* bird;
	GLfloat angle;
};
