#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Bird.h"

#define ZOOM_RATIO		(5.f)
#define DISPLACEMENT	(2)

class Tema1 : public SimpleScene
{
public:
	struct ViewportSpace
	{
		ViewportSpace() : x(0), y(0), width(1), height(1) {}
		ViewportSpace(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height) {}
		int x;
		int y;
		int width;
		int height;
	};

	struct LogicSpace
	{
		LogicSpace() : x(0), y(0), width(1), height(1) {}
		LogicSpace(float x, float y, float width, float height)
			: x(x), y(y), width(width), height(height) {}
		float x;
		float y;
		float width;
		float height;
	};

	Tema1();
	~Tema1();

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

	glm::mat3 modelMatrix, offsetMatrix;
	GLfloat centreX, centreY;
	GLboolean fall;

	GLfloat trueScore;
	GLint shownScore;

	Bird* bird;
	GLfloat angle;
};
