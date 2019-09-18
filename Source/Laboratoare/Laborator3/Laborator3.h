#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#define MOVE_RATIO			(.25f)
#define MOVE_RATIO_FAST		(.75f)
#define LIMIT				(.5f)
#define ROTATION_SPEEDUP	(1.25f)
#define SQUARE_SIDE			(100.f)
#define SQUARES_DISTANCE	(10.f)
#define START_FALL			(1000.f)

class Laborator3 : public SimpleScene
{
	public:
		Laborator3();
		~Laborator3();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix;
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;

		GLboolean moveRight;
		GLboolean moveRightFast;

		GLfloat translateXFast, translateYFall;
};
