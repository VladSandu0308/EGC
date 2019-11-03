#pragma once

#include <Core/Engine.h>

/* Represents an object in the scene as a mesh and a texture */
class TexturedRectangle
{
public:
	TexturedRectangle(
		GLfloat width,
		GLfloat height,
		const std::string& name,
		const std::string& texturePath);
	~TexturedRectangle();

	/* Returns the created mesh */
	Mesh* GetMesh();

	/* Returns the object's texture */
	Texture2D* GetTexture();

private:
	Mesh* mObstacle;
	Texture2D* texture;
};