#pragma once

#include <Core/GPU/Mesh.h>
#include <Component/SimpleScene.h>
#include <stb/stb_image.h>

#include "WormsUtils.h"

class Terrain
{
public:
	Terrain();
	~Terrain();

	/* Returns the deformed heightmap with all deformations applied */
	Texture2D* GetHeightTexture(GLfloat posX, GLfloat posY, GLfloat posZ);

	/* Allocates memory for the texture and assigns the hight map to it */
	GLvoid CreateHeightMap();

	/* Returns the texture used for the terrain */
	Texture2D* GetTexture();

	/* Returns the mesh used for the terrain */
	Mesh* GetMesh();

	/* Returns the shader used for the terrain */
	Shader* GetShader();

	/* Returns the height of the height map */
	GLint GetHeightMapHeight();

	/* Returns the width of the height map */
	GLint GetHeightMapWidth();

private:
	Texture2D* texture;
	Texture2D* heightTexture;
	Mesh* mesh;
	Shader* shader;
	GLubyte* heights;

	GLint numChannels;
	GLint terrainHeight;
	GLint terrainWidth;
};