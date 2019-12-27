#pragma once

#include "Terrain.h"

Terrain::Terrain()
{
	GLint numBytes;

	GLint index = 0;
	GLfloat posOX = 0.f;
	GLfloat posOZ = 0.f;

	/* Read the heightmap */
	heights = stbi_load(
		"Source/Teme/Tema3/Textures/heightmap.png",
		&terrainWidth,
		&terrainHeight,
		&numChannels,
		STBI_grey
	);

	numBytes = terrainHeight * terrainWidth * numChannels;

	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;

	for (GLushort i = 0; i != terrainHeight; ++i, posOZ += .03f)
	{
		posOX = 0.f;
		for (GLushort j = 0; j != terrainWidth; ++j, ++index, posOX += .03f)
		{
			/* Set the vertices for this row */
			vertices.emplace_back(glm::vec3(posOX, 1.f, posOZ));

			/* Set the indices */
			if (i != 0 && (j + 1) % terrainWidth)
			{
				/* Upper triangle */
				indices.push_back(index);
				indices.push_back(index - terrainWidth + 1);
				indices.push_back(index - terrainWidth);

				/* Lower triangle */
				indices.push_back(index);
				indices.push_back(index + 1);
				indices.push_back(index - terrainWidth + 1);
			}
		}
	}

	mesh = WormsUtils::CreateMesh("TerrainMesh", vertices, indices);

	shader = new Shader("TerrainShader");
	shader->AddShader(
		"Source/Teme/Tema3/Shaders/TerrainVS.glsl",
		GL_VERTEX_SHADER
	);
	shader->AddShader(
		"Source/Teme/Tema3/Shaders/TerrainFS.glsl",
		GL_FRAGMENT_SHADER
	);
	shader->CreateAndLink();

	CreateHeightMap();

	// TODO: baga textura
	texture = nullptr;
}

GLvoid Terrain::CreateHeightMap()
{
	GLuint randomTextureID;

	/* Generate and bind the new texture ID */
	glGenTextures(1, &randomTextureID);
	glBindTexture(GL_TEXTURE_2D, randomTextureID);

	/**
	* Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE)
	* using glTexParameteri
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	/* Use glTextImage2D to set the texture data */
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_R8,
		terrainWidth,
		terrainHeight,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		(void*)heights
	);

	/* Generate texture mip-maps */
	glGenerateMipmap(GL_TEXTURE_2D);

	/**
	* Save the texture into a wrapper Texture2D class for using easier later
	* during rendering phase
	*/
	heightTexture = new Texture2D();
	heightTexture->Init(randomTextureID, terrainWidth, terrainHeight, numChannels);
}

Terrain::~Terrain()
{
	delete shader;
	delete mesh;
	delete texture;
	delete heightTexture;
	delete[] heights;
}

Texture2D* Terrain::GetHeightTexture(GLfloat posX, GLfloat posY)
{
	// TODO: aplica deformari


	return heightTexture;
}

Texture2D* Terrain::GetTexture()
{
	return texture;
}

Mesh* Terrain::GetMesh()
{
	return mesh;
}

Shader* Terrain::GetShader()
{
	return shader;
}
