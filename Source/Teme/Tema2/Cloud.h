#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <random>

#include "Transform3D.h"

class Cloud
{
public:
	Cloud();
	~Cloud() = default;

	/* Returns the global mesh used for each component */
	static Mesh* GetMesh();

	/* Returns the global texture used for each component */
	static Texture2D* GetTexture();

	/* Returns the global shader used for each component */
	static Shader* GetShader();

	/* Initialises the mesh, shader and texture used by the cloud */
	static GLvoid Init();

	/* Initialises the mesh, shader and texture used by the cloud */
	static GLvoid Destroy();

	/**
	* Returns the number of components so PlaneRunner knows how many meshes to
	* render
	*/
	GLushort GetPartsNumber(GLfloat deltaTimeSeconds);

	/* Returns the model matrix of each component of the cloud */
	glm::mat4& GetModelMatrix(GLushort part);

private:
	glm::mat4 modelMatrix;
	
	static Texture2D* texture;
	static Mesh* mesh;
	static Shader* shader;

	GLfloat radiusOX, radiusOY;
	GLushort numParts;
	GLfloat angle;
	GLfloat speed;

	std::vector<GLfloat> deltaAngles;
	std::vector<GLfloat> deltaRadiiOX;
	std::vector<GLfloat> deltaRadiiOY;
	std::vector<GLfloat> scales;
};