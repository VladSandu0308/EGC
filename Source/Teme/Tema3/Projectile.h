#pragma once

#include <Core/Engine.h>

class Projectile
{
public:
	Projectile();
	~Projectile();

	/* Calculates the movement of the projectile */
	GLvoid MoveProjectile(GLfloat deltaTimeSeconds);

	/* Models the firing of a projectile */
	GLvoid Fire(
		GLfloat _posX,
		GLfloat _posY,
		GLfloat _posZ,
		GLfloat angleRadPitch,
		GLfloat angleRadYaw
	);

	/* Writes the position of the projectile in the given parameters */
	GLvoid GetPosition(GLfloat& _posX, GLfloat& _posY, GLfloat& _posZ);

	/* Returns the radius of the projectile */
	GLfloat GetRadius();

	/* Returns the projectile's mesh */
	Mesh* GetMesh();

	/* Returns the projectile's mesh */
	Shader* GetShader();

	/* Returns the projectile's mesh */
	Texture2D* GetTexture();

	/* Returns whether the projectile should be visible or not */
	GLboolean HasBeenFired();

	/* Signals that the projectile should no longer be visible */
	GLvoid NotFired();

private:
	const GLfloat initialSpeed;
	const GLfloat radius;
	const GLfloat gravity;
	
	GLfloat speedOY, speedOX, speedOZ;
	GLfloat posX, posY, posZ;
	GLboolean fired;

	Shader* shader;
	Mesh* mesh;
	Texture2D* texture;
};