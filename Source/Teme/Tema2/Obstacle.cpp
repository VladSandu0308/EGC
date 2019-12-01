#include "Obstacle.h"

const GLfloat Obstacle::maxScale = 1.f;
const GLfloat Obstacle::minScale = 0.3f;

Mesh* Obstacle::mesh			= nullptr;
Texture2D* Obstacle::texture	= nullptr;
Shader* Obstacle::shader		= nullptr;

Obstacle::Obstacle()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<GLfloat> angleDist(180.f, 360.f);
	std::uniform_real_distribution<GLfloat> speedDist(10.f, 20.f);
	std::uniform_real_distribution<GLfloat> radiusDistOX(10.f, 20.f);
	std::uniform_real_distribution<GLfloat> radiusDistOY(2.f, 6.f);
	std::uniform_real_distribution<GLfloat> accelerationDist(.5f, 2.f);
	std::uniform_real_distribution<GLfloat> scaleSpeedDist(.5f, 1.f);
	std::uniform_real_distribution<GLfloat> scaleDist(minScale, maxScale);
	std::uniform_real_distribution<GLfloat> rotSpeedDist(10.f, 100.f);

	radiusOX		= radiusDistOX(gen);
	radiusOY		= radiusDistOY(gen);
	angle			= angleDist(gen);
	scale			= scaleDist(gen);
	speed			= speedDist(gen);
	acceleration	= accelerationDist(gen);
	scaleSpeed		= scaleSpeedDist(gen);
	speedOX			= rotSpeedDist(gen);
	speedOY			= rotSpeedDist(gen);
	speedOZ			= rotSpeedDist(gen);
	variable		= rand() % 2;
	scaleType		= 1.f;
	angleOX			= 0.f;
	angleOY			= 0.f;
	angleOZ			= 0.f;
}

glm::mat4& Obstacle::GetModelMatrix(GLfloat deltaTimeSeconds)
{
	speed += acceleration * deltaTimeSeconds;
	angle += speed * deltaTimeSeconds;
	angle = angle > 360.f ? 0.f : angle;

	if (variable)
	{
		scale += scaleType * scaleSpeed * deltaTimeSeconds;

		if (scale >= maxScale || scale <= minScale)
		{
			scaleType = -scaleType;
		}
	}

	angleOX += speedOX * deltaTimeSeconds;
	angleOX = angleOX > 360.f ? 0.f : angleOX;

	angleOY += speedOY * deltaTimeSeconds;
	angleOY = angleOY > 360.f ? 0.f : angleOY;

	angleOZ += speedOZ * deltaTimeSeconds;
	angleOZ = angleOZ > 360.f ? 0.f : angleOZ;

	modelMatrix = Transform3D::Translate(
		cos(RADIANS(angle)) * radiusOX,
		sin(RADIANS(angle)) * radiusOY,
		0.f
	);
	modelMatrix *= Transform3D::Scale(scale, scale, scale);
	modelMatrix *= Transform3D::RotateOZ(RADIANS(angleOZ));
	modelMatrix *= Transform3D::RotateOY(RADIANS(angleOY));
	modelMatrix *= Transform3D::RotateOX(RADIANS(angleOX));

	return modelMatrix;
}

GLvoid Obstacle::Init()
{
	mesh = new Mesh("sphere");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");

	texture = new Texture2D();
	texture->Load2D("Source/Teme/Tema2/Textures/rock.jpg");

	shader = new Shader("ObstacleShader");
	shader->AddShader("Source/Teme/Tema2/Shaders/ObjectVertex.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Teme/Tema2/Shaders/ObjectFragment.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
}

GLvoid Obstacle::Destroy()
{
	delete mesh;
	delete texture;
	delete shader;
}

Mesh* Obstacle::GetMesh()
{
	return mesh;
}

Texture2D* Obstacle::GetTexture()
{
	return texture;
}

Shader* Obstacle::GetShader()
{
	return shader;
}

GLfloat Obstacle::GetRadius()
{
	return scale / 2.f;
}
