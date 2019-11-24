#include "Obstacle.h"

const GLfloat Obstacle::maxScale = 1.5f;
const GLfloat Obstacle::minScale = 0.5f;

Mesh* Obstacle::obstacle = nullptr;
Texture2D* Obstacle::texture = nullptr;
Shader* Obstacle::shader = nullptr;

Obstacle::Obstacle(
	GLfloat _radiusOX,
	GLfloat _radiusOY,
	GLfloat _speed,
	GLfloat _acceleration,
	GLfloat _scale,
	GLfloat _scaleSpeed,
	GLboolean _variable
) :
	acceleration(_acceleration),
	variable(_variable),
	radiusOX(_radiusOX),
	radiusOY(_radiusOY),
	scaleSpeed(_scaleSpeed),
	speedOX(50.f), speedOY(50.f), speedOZ(50.f)
{
	speed		= _speed;
	scale		= _scale;
	speed		= _speed;
	angle		= -90.f;
	scaleType	= 1.f;
	angleOX		= 0.f;
	angleOY		= 0.f;
	angleOZ		= 0.f;
}

Obstacle::~Obstacle()
{
	delete obstacle;
	delete texture;
	delete shader;
}

glm::mat4& Obstacle::GetModelMatrix(GLfloat deltaTimeSeconds)
{
	speed += acceleration * deltaTimeSeconds;
	angle += speed * deltaTimeSeconds;

	if (angle >= 360.f)
	{
		angle = 0.f;
	}

	if (variable)
	{
		scale += scaleType * scaleSpeed * deltaTimeSeconds;

		if (scale >= maxScale || scale <= minScale)
		{
			scaleType = -scaleType;
		}
	}

	angleOX += speedOX * deltaTimeSeconds;
	if (angleOX >= 360.f)
	{
		angleOX = 0.f;
	}

	angleOY += speedOY * deltaTimeSeconds;
	if (angleOY >= 360.f)
	{
		angleOY = 0.f;
	}

	angleOZ += speedOZ * deltaTimeSeconds;
	if (angleOZ >= 360.f)
	{
		angleOZ = 0.f;
	}

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
	obstacle = new Mesh("sphere");
	obstacle->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");

	texture = new Texture2D();
	texture->Load2D("Source/Teme/Tema2/Textures/rock.jpg");

	shader = new Shader("ObstacleShader");
	shader->AddShader("Source/Teme/Tema2/Shaders/ObjectVertex.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Teme/Tema2/Shaders/ObjectFragment.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
}

Mesh* Obstacle::GetMesh()
{
	return obstacle;
}

Texture2D* Obstacle::GetTexture()
{
	return texture;
}

Shader* Obstacle::GetShader()
{
	return shader;
}