#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1():
	colourCase(0), objectCase(0), posX(0.f), posY(0.f), posZ(0.f)
{
	changeClearColour();
	changeObject();
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* boxMesh = new Mesh("box");
		boxMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[boxMesh->GetMeshID()] = boxMesh;

		Mesh* sphereMesh = new Mesh("sphere");
		sphereMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[sphereMesh->GetMeshID()] = sphereMesh;

		Mesh* teapotMesh = new Mesh("teapot");
		teapotMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[teapotMesh->GetMeshID()] = teapotMesh;

		Mesh* archerMesh = new Mesh("archer");
		archerMesh->LoadMesh(RESOURCE_PATH::MODELS + "Characters\\Archer", "Archer.fbx");
		meshes[archerMesh->GetMeshID()] = archerMesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(clearRed, clearGreen, clearBlue, 1.f);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1.f, 0.5f, 0.f), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1.f, 0.5f, 0.f));

	// render the 3rd object
	RenderMesh(meshes[objName], glm::vec3(posX, posY, posZ), objScale);
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (window->KeyHold(GLFW_KEY_R))
		{
			degrees += SPEED_FACTOR * deltaTime;
			if (degrees > 360.f)
			{
				degrees = 0.f;
			}

			posX += RANGE * cos(degrees);
			posY += RANGE * sin(degrees);
		}

		// treat continuous update based on input
		if (window->KeyHold(GLFW_KEY_W))
		{
			posZ -= deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_S))
		{
			posZ += deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_A))
		{
			posX -= deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_D))
		{
			posX += deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_Q))
		{
			posY -= deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_E))
		{
			posY += deltaTime * SPEED_FACTOR;
		}
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_C) {
		colourCase = (colourCase + 1) % NUM_COLOURS;

		changeClearColour();
	}

	if (key == GLFW_KEY_X) {
		objectCase = (objectCase + 1) % NUM_OBJECTS;

		changeObject();
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}

void Laborator1::changeClearColour()
{
	switch (colourCase)
	{
	case 1:
		clearRed	= 0.286f;
		clearGreen	= 0.074f;
		clearBlue	= 0.184f;
		break;
	
	case 2:
		clearRed	= 0.635f;
		clearGreen	= 0.086f;
		clearBlue	= 0.376f;
		break;
	
	case 3:
		clearRed	= 0.811f;
		clearGreen	= 0.188f;
		clearBlue	= 0.517f;
		break;

	default:
		clearRed	= 0.f;
		clearGreen	= 0.f;
		clearBlue	= 0.f;
		break;
	}
}

void Laborator1::changeObject()
{
	switch (objectCase)
	{
	case 1:
		objName		= "sphere";
		objScale	= glm::vec3(1.f);
		break;

	case 2:
		objName		= "teapot";
		objScale	= glm::vec3(1.f);
		break;

	default:
		objName		= "archer";
		objScale	= glm::vec3(0.01f);
		break;
	}
}
