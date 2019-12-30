#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

#include <Windows.h>
#include <mmsystem.h>

#include "Player.h"
#include "Terrain.h"
#include "Projectile.h"

#pragma comment(lib, "winmm.lib")

class Worms : public SimpleScene
{
public:
	Worms();
	~Worms();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	/* Renders a mesh particularised by id */
	GLvoid RenderMesh(
		Mesh* mesh,
		Shader* shader,
		const glm::mat4& modelMatrix,
		Texture2D* texture
	);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat4 modelMatrix;

	Terrain* terrain;
	Projectile* projectile;
	std::vector<Player> players;

	GLfloat posX, posY, posZ;

	glm::vec3 lightPosition1;
	glm::vec3 lightPosition2;
	glm::vec3 lightDirection;
	GLuint materialShininess;
	GLfloat materialKd;
	GLfloat materialKs;

	GLfloat cutOffAngle;

	GLushort crtPlayer;
};