#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = SQUARE_SIDE;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;
	
	// initialize tx and ty (the translation steps)
	translateX		= 0.f;
	translateY		= 0.f;

	translateXFast	= 0.f;
	translateYFall  = resolution.y;

	// initialise moving directions
	moveRight		= false;
	moveRightFast	= false;

	// initialize sx and sy (the scale factors)
	scaleX			= 1.f;
	scaleY			= 1.f;
	
	// initialize angularStep
	angularStep		= 0.f;
	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// Update steps for translation, rotation, scale, in order to create animations
	glm::ivec2 resolution = window->GetResolution();
	
	{
		modelMatrix = Transform2D::Translate(150, 250);

		// Create animations by multiplying current transform matrix with matrices from Transform 2D
		if (moveRight)
		{
			translateX += MOVE_RATIO * deltaTimeSeconds * resolution.x;
			modelMatrix *= Transform2D::Translate(translateX, translateY);
			
			if (translateX > resolution.x * LIMIT)
			{
				moveRight = false;
			}
				
		} else
		{
			translateX -= MOVE_RATIO * deltaTimeSeconds * resolution.x;
			modelMatrix *= Transform2D::Translate(translateX, translateY);
			
			if (translateX <= 0)
			{
				moveRight = true;
			}
		}

		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = Transform2D::Translate(400, 250);
		// Create animations by multiplying current transform matrix with matrices from Transform 2D

		angularStep += deltaTimeSeconds;
		modelMatrix *= Transform2D::Translate(SQUARE_SIDE / 2, SQUARE_SIDE / 2);
		modelMatrix *= Transform2D::Rotate(angularStep);
		modelMatrix *= Transform2D::Translate(-SQUARE_SIDE / 2, -SQUARE_SIDE / 2);

		RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = Transform2D::Translate(650, 250);

		// Create animations by multiplying current transform matrix with matrices from Transform 2D
		scaleX += 4.5f * M_1_PI * deltaTimeSeconds;
		scaleY += 4.5f * M_1_PI * deltaTimeSeconds;

		modelMatrix *= Transform2D::Translate(SQUARE_SIDE / 2, SQUARE_SIDE / 2);
		modelMatrix *= Transform2D::Scale(sin(scaleX), sin(scaleY));
		modelMatrix *= Transform2D::Translate(-SQUARE_SIDE / 2, -SQUARE_SIDE / 2);

		RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
	}

	// BONUS: some fancier rotations and faster movement
	{
		modelMatrix = Transform2D::Translate(150, 250);

		// Create animations by multiplying current transform matrix with matrices from Transform 2D
		if (moveRightFast)
		{
			translateXFast += MOVE_RATIO_FAST * deltaTimeSeconds * resolution.x;
			modelMatrix *= Transform2D::Translate(translateXFast, translateY);

			if (translateXFast > resolution.x * LIMIT)
			{
				moveRightFast = false;
			}

		}
		else
		{
			translateXFast -= MOVE_RATIO_FAST * deltaTimeSeconds * resolution.x;
			modelMatrix *= Transform2D::Translate(translateXFast, translateY);

			if (translateXFast <= 0)
			{
				moveRightFast = true;
			}
		}

		RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = Transform2D::Translate(150, 250);
		// Create animations by multiplying current transform matrix with matrices from Transform 2D

		modelMatrix *= Transform2D::Translate(translateX + SQUARE_SIDE / 2, translateY + SQUARE_SIDE / 2);
		modelMatrix *= Transform2D::Rotate(angularStep);
		modelMatrix *= Transform2D::Translate(-translateX + SQUARE_SIDE / 2, -translateY + SQUARE_SIDE / 2);
		modelMatrix *= Transform2D::Translate(translateX + SQUARES_DISTANCE, 0);

		RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
	}

	{
		translateYFall -= MOVE_RATIO * deltaTimeSeconds * resolution.y;
		modelMatrix = Transform2D::Translate(START_FALL, translateYFall);

		// Create animations by multiplying current transform matrix with matrices from Transform 2D
		modelMatrix *= Transform2D::Translate(SQUARE_SIDE / 2, SQUARE_SIDE / 2);
		modelMatrix *= Transform2D::Rotate(-angularStep * ROTATION_SPEEDUP);
		modelMatrix *= Transform2D::Translate(-SQUARE_SIDE / 2, -SQUARE_SIDE / 2);

		if (translateYFall <= 0)
		{
			translateYFall = resolution.y;
		}

		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
	}
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
