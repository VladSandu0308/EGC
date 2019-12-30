#include "Projectile.h"

Projectile::Projectile() :
	initialSpeed(3.5f),
	gravity(2.f),
	radius(.02f),
	scale(2.f * radius),
	fired(GLFW_FALSE)
{
	/* Read and compile the shader for the projectile */
	{
		shader = new Shader("ProjectileShader");
		shader->AddShader(
			"Source/Teme/Tema3/Shaders/ProjectileVS.glsl",
			GL_VERTEX_SHADER
		);
		shader->AddShader(
			"Source/Teme/Tema3/Shaders/ProjectileFS.glsl",
			GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
	}

	/* Read and send the texture to the GPU */
	{
		texture = new Texture2D();
		texture->Load2D(
			"Source/Teme/Tema3/Textures/projectile_texture.jpg",
			GL_REPEAT
		);
	}

	/* Read and create the mesh for the projectile */
	{
		mesh = new Mesh("ProjectileMesh");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	}
}

Projectile::~Projectile()
{
	delete shader;
	delete mesh;
	delete texture;
}

GLvoid Projectile::Fire(
	GLfloat _posX,
	GLfloat _posY,
	GLfloat _posZ,
	GLfloat angleRadPitch,
	GLfloat angleRadYaw
)
{
	posX	= _posX;
	posY	= _posY;
	posZ	= _posZ;

	fired	= GLFW_TRUE;

	speedOY	= initialSpeed * sin(angleRadPitch);
	speedOZ = initialSpeed * cos(angleRadPitch) * cos(angleRadYaw);
	speedOX = initialSpeed * cos(angleRadPitch) * sin(angleRadYaw);
}

GLvoid Projectile::MoveProjectile(GLfloat deltaTimeSeconds)
{
	/* The law of Galilei */
	speedOY -= gravity * deltaTimeSeconds;

	posY +=
		speedOY * deltaTimeSeconds
		+ gravity * deltaTimeSeconds * deltaTimeSeconds / 2.f;

	posZ += speedOZ * deltaTimeSeconds;
	posX += speedOX * deltaTimeSeconds;
}

GLvoid Projectile::NotFired()
{
	fired = GLFW_FALSE;
}

GLvoid Projectile::GetPosition(GLfloat& _posX, GLfloat& _posY, GLfloat& _posZ)
{
	_posX = posX;
	_posY = posY;
	_posZ = posZ;
}

glm::mat4& Projectile::GetModelMatrix()
{
	modelMatrix = Transform3D::Translate(posX, posY, posZ);
	modelMatrix *= Transform3D::Scale(scale, scale, scale);

	return modelMatrix;
}

GLfloat Projectile::GetRadius()
{
	return radius;
}

GLfloat Projectile::GetBlastRadius()
{
	return radius * 5.f;
}

Mesh* Projectile::GetMesh()
{
	return mesh;
}

Shader* Projectile::GetShader()
{
	return shader;
}

Texture2D* Projectile::GetTexture()
{
	return texture;
}

GLboolean Projectile::HasBeenFired()
{
	return fired;
}