#pragma once

#include <Component/SimpleScene.h>

#define NUM_COLOURS		(4)
#define NUM_OBJECTS		(3)
#define SPEED_FACTOR	(2.f)
#define RANGE			(.02f)

class Laborator1 : public SimpleScene
{
	public:
		Laborator1();
		~Laborator1();

		void Init() override;

	private:
		GLuint colourCase, objectCase;
		GLfloat clearRed, clearGreen, clearBlue;
		
		std::string objName;
		glm::vec3 objScale;

		GLfloat posX, posY, posZ;

		GLfloat degrees;

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
		void changeClearColour();
		void changeObject();
};
