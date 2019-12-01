#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <random>

#include "Transform3D.h"

class Fuel
{
public:
	Fuel();
	~Fuel() = default;

	/**
	* Calculates the movement of the jerry can as a maodel matrix and returns
	* it
	*/
	glm::mat4& GetModelMatrix(GLfloat deltaTimeSeconds);

	/* Returns the radius of the fuel can */
	GLfloat GetRadius();

	/* Returns the amount of fuel in the jerry can */
	GLfloat GetFuelAmount();
	
	/* Returns the jerry can mesh */
	static Mesh* GetMesh();

	/* Returns the jerry can texture */
	static Texture2D* GetTexture();

	/* Returns the jerry can shader */
	static Shader* GetShader();

	/* Initialises the mesh, shader and texture used to render the jerry can */
	static GLvoid Init();

	/* Destroys the mesh, shader and texture used to render the jerry can */
	static GLvoid Destroy();

private:
	glm::mat4 modelMatrix;

	static Mesh* mesh;
	static Texture2D* texture;
	static Shader* shader;

	static const GLfloat maxScale;
	static const GLfloat minScale;

	GLfloat acceleration;
	GLboolean variable;
	GLfloat radiusOX, radiusOY;
	GLfloat scaleSpeed;

	GLfloat speedOX, speedOY, speedOZ;

	GLfloat scaleType;
	GLfloat scale;
	GLfloat speed;
	GLfloat angle;

	GLfloat angleOX, angleOY, angleOZ;
};
