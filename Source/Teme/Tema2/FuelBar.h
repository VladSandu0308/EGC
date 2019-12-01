#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>

#include "Utils.h"

#include "Transform3D.h"

class FuelBar
{
public:
	FuelBar();
	~FuelBar();

	/* Getters for the 2 meshes contained */
	Mesh* GetBackground();

	/**
	* Also sets the scale factor as the ratio of the current and the maximum
	* fuel
	*/
	Mesh* GetFuel(
		GLfloat deltaTimeSeconds,
		GLfloat& scaleFactor
	);

	/* Updates the amount of fuel and checks if there is any left */
	GLboolean HasFuel(GLfloat deltaTimeSeconds);


	/* Adds an amount of fuel that was collected from a jerry can */
	GLvoid AddFuel(GLfloat amount);

private:
	Mesh* background;
	Mesh* fuel;

	const GLfloat maxFuel;
	const GLfloat decay;

	GLfloat crtFuel;
};