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
		GLfloat update,
		GLfloat deltaTimeSeconds,
		GLfloat& scaleFactor);

private:
	Mesh* background;
	Mesh* fuel;

	const GLfloat maxFuel;
	const GLfloat decay;

	GLfloat crtFuel;
};