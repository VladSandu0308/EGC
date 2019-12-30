#include "Player.h"

Shader* Player::shader				= nullptr;

Mesh* Player::bearMesh				= nullptr;
Mesh* Player::bazookaMesh			= nullptr;

Texture2D* Player::bazookaTexture	= nullptr;
Texture2D* Player::bearTexture		= nullptr;

Player::Player(
	GLfloat _posX,
	GLfloat _posY,
	GLfloat _posZ,
	GLfloat initialAngle
) :
	posX(_posX),
	posY(_posY),
	posZ(_posZ),
	hitSphereRadius(1.f),
	angularSpeed(100.f),
	bazookaConstructionOffsetX(-0.043f),
	bazookaConstructionOffsetY(.011f),
	bazookaConstructionOffsetZ(.052f),
	bazookaOffsetX(0.f),
	bazookaOffsetY(.015f),
	bazookaOffsetZ(-.035f),
	bazookaLen(0.086f),
	bazookaScale(2.f),
	anglePitch(0.f),
	angleYaw(90.f - initialAngle),
	bearScale(0.2f),
	bearConstructionOffsetX(-.05f),
	bearConstructionOffsetY(-2.5f),
	bearConstructionOffsetZ(-2.2f),
	alive(GLFW_TRUE)
{
}

Player::~Player()
{
}

GLvoid Player::Init()
{
	/* Read and compile the shader */
	{
		shader = new Shader("BearShader");
		shader->AddShader(
			"Source/Teme/Tema3/Shaders/ProjectileVS.glsl",
			GL_VERTEX_SHADER
		);
		shader->AddShader(
			"Source/Teme/Tema3/Shaders/ProjectileFS.glsl",
			GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
	}

	/* Read and send the bazooka texture to the GPU */
	{
		bazookaTexture = new Texture2D();
		bazookaTexture->Load2D(
			"Source/Teme/Tema3/Textures/bazooka_texture.png",
			GL_REPEAT
		);
	}

	/* Create the bazoka mesh */
	{
		bazookaMesh = new Mesh("BazookaMesh");
		bazookaMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "bazooka.fbx");
	}

	/* Read and send the bear texture to the GPU */
	{
		bearTexture = new Texture2D();
		bearTexture->Load2D(
			"Source/Teme/Tema3/Textures/bear_texture.png",
			GL_REPEAT
		);
	}

	/* Create the bear mesh */
	{
		bearMesh = new Mesh("MushroomMesh");
		bearMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "bear.fbx");
	}
}

GLvoid Player::Destroy()
{
	delete shader;
	delete bearMesh;
	delete bearTexture;
	delete bazookaMesh;
	delete bazookaTexture;
}

GLvoid Player::UpdateAngles(GLfloat deltaTimeYaw, GLfloat deltaTimePitch)
{
	anglePitch	-= angularSpeed * deltaTimePitch;
	angleYaw	+= angularSpeed * deltaTimeYaw;
}

glm::mat4& Player::GetBearModelMatrix()
{
	/* Calculate the model matrix */
	modelMatrix = Transform3D::Translate(posX, posY, posZ);
	modelMatrix *= Transform3D::RotateOY(RADIANS((angleYaw - 90.f)));
	modelMatrix *= Transform3D::RotateOX(RADIANS(-90.f));
	modelMatrix *= Transform3D::Scale(bearScale, bearScale, bearScale);
	modelMatrix *= Transform3D::Translate(
		bearConstructionOffsetX,
		bearConstructionOffsetY,
		bearConstructionOffsetZ
	);

	return modelMatrix;
}

glm::mat4& Player::GetBazookaModelMatrix()
{
	/* Calculate the model matrix */
	modelMatrix = Transform3D::Translate(posX, posY, posZ);
	modelMatrix *= Transform3D::RotateOY(RADIANS(angleYaw));
	modelMatrix *= Transform3D::Translate(
		bazookaOffsetX,
		bazookaOffsetY,
		bazookaOffsetZ
	);
	modelMatrix *= Transform3D::RotateOZ(RADIANS(anglePitch));
	modelMatrix *= Transform3D::Scale(bazookaScale, bazookaScale, bazookaScale);
	modelMatrix *= Transform3D::Translate(
		bazookaConstructionOffsetX,
		bazookaConstructionOffsetY,
		bazookaConstructionOffsetZ
	);

	return modelMatrix;
}

GLvoid Player::GetProjectileStartPos(
	GLfloat& _posX,
	GLfloat& _posY,
	GLfloat& _posZ
)
{
	/* Calculate the model matrix and get the starting point */
	modelMatrix = Transform3D::Translate(posX, posY, posZ);
	modelMatrix *= Transform3D::RotateOY(RADIANS(angleYaw));
	modelMatrix *= Transform3D::Translate(
		bazookaOffsetX,
		bazookaOffsetY,
		bazookaOffsetZ
	);
	modelMatrix *= Transform3D::RotateOZ(RADIANS(anglePitch));
	modelMatrix *= Transform3D::Translate(-bazookaLen, 0.f, 0.f);

	_posX = modelMatrix[3][0];
	_posY = modelMatrix[3][1];
	_posZ = modelMatrix[3][2];
}

GLboolean Player::CheckCollision(
	GLfloat projectileX,
	GLfloat projectileY,
	GLfloat projectileZ,
	GLfloat radius
)
{
	/* There's no point checking collision with a dead bear */
	if (!alive)
	{
		return GLFW_FALSE;
	}

	/* Collision between 2 spheres */
	if ((projectileX - posX) * (projectileX - posX)
		+ (projectileY - posY) * (projectileY - posY)
		+ (projectileZ - posZ) * (projectileZ - posZ)
		<= (radius + hitSphereRadius) * (radius + hitSphereRadius))
	{
		alive = GLFW_FALSE;
		PlaySound(TEXT("gotcha.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return GLFW_TRUE;
	}

	return GLFW_FALSE;
}

GLboolean Player::IsAlive()
{
	return alive;
}

GLfloat Player::GetAnglePitch()
{
	return -anglePitch;
}

GLfloat Player::GetAngleYaw()
{
	return angleYaw - 90.f;
}

Shader* Player::GetShader()
{
	return shader;
}

Mesh* Player::GetBearMesh()
{
	return bearMesh;
}

Texture2D* Player::GetBearTexture()
{
	return bearTexture;
}

Mesh* Player::GetBazookaMesh()
{
	return bazookaMesh;
}

Texture2D* Player::GetBazookaTexture()
{
	return bazookaTexture;
}