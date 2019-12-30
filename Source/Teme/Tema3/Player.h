#pragma once

#include <Core/Engine.h>

#include "Transform3D.h"

class Player
{
public:
	Player(
		GLfloat _posX,
		GLfloat _posY,
		GLfloat _posZ,
		GLfloat initialAngle
	);

	~Player();

	/**
	*	Creates all meshes, textures and shaders.
	*	To be called only once.
	*/
	static GLvoid Init();

	/**
	*	Updates the angles of the mushroom and bazooka.
	*	If there is no movement in a direction, its corresponding deltaTime is 0.
	*/
	GLvoid UpdateAngles(GLfloat deltaTimeYaw, GLfloat deltaTimePitch);

	/* Returns the shader used for the mushroom and bazooka */
	Shader* GetShader();
	
	/* Returns the mesh used for the mushroom */
	Mesh* GetBearMesh();
	
	/* Returns the texture used for the mushroom */
	Texture2D* GetBearTexture();

	/* Returns the mesh used for the bazooka */
	Mesh* GetBazookaMesh();

	/* Returns the texture used for the bazooka */
	Texture2D* GetBazookaTexture();

	/**	Returns the model matrix for the mushroom */
	glm::mat4& GetBearModelMatrix();

	/*	Returns the model matrix for the bazooka */
	glm::mat4& GetBazookaModelMatrix();

	/* Returns the point where the projectile leaves the barrel of the bazooka */
	GLvoid GetProjectileStartPos(
		GLfloat& _posX,
		GLfloat& _posY,
		GLfloat& _posZ
	);

	/* Returns the pitch angle of the bazooka */
	GLfloat GetAnglePitch();

	/* Returns the yaw angle of the bazooka */
	GLfloat GetAngleYaw();

	/**
	*	Destroys all meshes, textures and shaders.
	*	To be called only once.
	*/
	static GLvoid Destroy();

private:
	const GLfloat angularSpeed;
	const GLfloat posX, posY, posZ;

	const GLfloat bearScale;
	const GLfloat bearConstructionOffsetX;
	const GLfloat bearConstructionOffsetY;
	const GLfloat bearConstructionOffsetZ;

	const GLfloat bazookaOffsetX, bazookaOffsetY, bazookaOffsetZ;
	const GLfloat bazookaConstructionOffsetX;
	const GLfloat bazookaConstructionOffsetY;
	const GLfloat bazookaConstructionOffsetZ;
	const GLfloat bazookaLen;
	const GLfloat bazookaScale;

	glm::mat4 modelMatrix;
	
	GLfloat anglePitch, angleYaw;

	static Shader* shader;
	
	static Mesh* bearMesh;
	static Texture2D* bearTexture;

	static Mesh* bazookaMesh;
	static Texture2D* bazookaTexture;
};