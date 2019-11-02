#include "Bird.h"

Bird::Bird() :
	wingDirection(1.f),
	wingSpeed(200.f),
	headRadius(23.f),
	bodyRadiusX(45.f),
	bodyRadiusY(30.f),
	eyeRadius(7.5f),
	numTriangles(20),
	wingAcceleration(30.f),
	hitBoxRadiusX(70.f),
	hitBoxRadiusY(30.f),
	numTrianglesHBox(15)
{
	GLfloat arg;
	wingHeight = 70.f;

	/* Generate the bird's head */
	{
		mHead = new Mesh("head");
		
		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;

		vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 0.f));

		for (GLushort i = 0; i < numTriangles; ++i)
		{
			arg = 2.0f * (GLfloat)M_PI * i / numTriangles;

			vertices.emplace_back(
				glm::vec3(cos(arg) * headRadius, sin(arg) * headRadius, 0),
				glm::vec3(0.811f, 0.188f, 0.517f));
			indices.push_back(i);
		}
		indices.push_back(numTriangles);
		indices.push_back(1);

		mHead->InitFromData(vertices, indices);
		mHead->SetDrawMode(GL_TRIANGLE_FAN);

		headOffsetX = 35.f;
		headOffsetY = 0.f;
	}

	/* Generate the bird's body */
	{
		mBody = new Mesh("body");

		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;

		vertices.emplace_back(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 1.f));

		for (GLushort i = 0; i < numTriangles; ++i)
		{
			arg = 2.0f * (GLfloat)M_PI * i / numTriangles;

			vertices.emplace_back(
				glm::vec3(cos(arg) * bodyRadiusX, sin(arg) * bodyRadiusY, 0),
				glm::vec3(0.635f, 0.086f, 0.376f));
			indices.push_back(i);
		}
		indices.push_back(numTriangles);
		indices.push_back(1);

		mBody->InitFromData(vertices, indices);
		mBody->SetDrawMode(GL_TRIANGLE_FAN);

		bodyOffsetX = -20.f;
		bodyOffsetY = 0.f;
	}

	/* Generate the bird's eye */
	{
		mEye = new Mesh("eye");

		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;

		vertices.emplace_back(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f));

		for (GLushort i = 0; i < numTriangles; ++i)
		{
			arg = 2.0f * (GLfloat)M_PI * i / numTriangles;

			vertices.emplace_back(
				glm::vec3(cos(arg) * eyeRadius, sin(arg) * eyeRadius, 0),
				glm::vec3(1.f, 1.f, 1.f));
			indices.push_back(i);
		}
		indices.push_back(numTriangles);
		indices.push_back(1);

		mEye->InitFromData(vertices, indices);
		mEye->SetDrawMode(GL_TRIANGLE_FAN);

		eyeOffsetX = 50.f;
		eyeOffsetY = 10.f;
	}

	/* Generate the bird's beak */
	{
		mBeak = new Mesh("beak");

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.682f, 0.258f)),
			VertexFormat(glm::vec3(0.f, -15.f, 0.f), glm::vec3(1.0f, 0.682f, 0.258f)),
			VertexFormat(glm::vec3(20.f, -7.5f, 0.f), glm::vec3(1.0f, 0.682f, 0.258f))
		};
		std::vector<GLushort> indices =
		{
			0, 1, 2
		};

		mBeak->InitFromData(vertices, indices);

		beakOffsetX = 50.f;
		beakOffsetY = 0.f;
	}

	/* Generate the bird's tail */
	{
		mTail = new Mesh("tail");

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-50.f, 15.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-50.f, -15.f, 0.f), glm::vec3(0.f, 0.f, 1.f))
		};
		std::vector<GLushort> indices =
		{
			0, 1, 2
		};

		mTail->InitFromData(vertices, indices);

		tailOffsetX = -50.f;
		tailOffsetY = 0.f;
	}

	/* Generate the bird's wing */
	{
		mWing = new Mesh("wing");

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(.75f, 1.f, 0.f)),
			VertexFormat(glm::vec3(50.f, 0.f, 0.f), glm::vec3(.75f, 1.f, 0.f)),
			VertexFormat(glm::vec3(25.f, wingHeight, 0.f), glm::vec3(1.f, 0.f, 0.f))
		};
		std::vector<GLushort> indices =
		{
			0, 1, 2
		};

		mWing->InitFromData(vertices, indices);

		wingOffsetX = -50.f;
		wingOffsetY = 0.f;
	}

	/* Generate the bird's hit box (vector and the mesh) */
	{
		mHitBox = new Mesh("mHitBox");

		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;

		vertices.emplace_back(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(1.f, 0.f, 0.f));

		for (GLushort i = 0; i < numTrianglesHBox; ++i)
		{
			arg = 2.0f * (GLfloat)M_PI * i / numTrianglesHBox;

			vertices.emplace_back(
				glm::vec3(cos(arg) * hitBoxRadiusX, sin(arg) * hitBoxRadiusY, 0),
				glm::vec3(1.f, 0.f, 0.f));
			indices.push_back(i);
			hitBox.emplace_back(cos(arg) * 70.f, sin(arg) * 30.f);
		}
		indices.push_back(numTrianglesHBox);
		indices.push_back(1);

		mHitBox->InitFromData(vertices, indices);
		mHitBox->SetDrawMode(GL_TRIANGLE_FAN);

		hitBoxOffsetX = 0.f;
		hitBoxOffsetY = 0.f;
	}
}

void Bird::FlapWing(GLfloat deltaTimeSeconds)
{
	/* Flap the wing by changing the upper vertex of the triangle its triangle */
	wingHeight	+= wingDirection * deltaTimeSeconds * wingSpeed;
	wingSpeed	+= deltaTimeSeconds * wingAcceleration;

	if (wingHeight >= 70.f)
	{
		wingHeight = 70.f;
		wingDirection *= -1;
	}
	else if (wingHeight <= -70.f)
	{
		wingHeight = -70.f;
		wingDirection *= -1;
	}

	delete mWing;
	mWing = new Mesh("wing");

	/* Create a new mesh  */
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(.75f, 1.f, 0.f)),
		VertexFormat(glm::vec3(50.f, 0.f, 0.f), glm::vec3(.75f, 1.f, 0.f)),
		VertexFormat(glm::vec3(25.f, wingHeight, 0.f), glm::vec3(.75f, 1.f, 0.f))
	};
	std::vector<GLushort> indices =
	{
		0, 1, 2
	};

	mWing->InitFromData(vertices, indices);
}

Bird::~Bird()
{
	delete mHead;
	delete mBody;
	delete mBeak;
	delete mEye;
	delete mWing;
	delete mTail;
}

Mesh* Bird::GetHeadMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = headOffsetX;
	offsetY = headOffsetY;

	return mHead;
}

Mesh* Bird::GetBeakMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = beakOffsetX;
	offsetY = beakOffsetY;

	return mBeak;
}

Mesh* Bird::GetEyeMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = eyeOffsetX;
	offsetY = eyeOffsetY;

	return mEye;
}

Mesh* Bird::GetWingMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = wingOffsetX;
	offsetY = wingOffsetY;

	return mWing;
}

Mesh* Bird::GetBodyMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = bodyOffsetX;
	offsetY = bodyOffsetY;

	return mBody;
}

Mesh* Bird::GetTailMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = tailOffsetX;
	offsetY = tailOffsetY;

	return mTail;
}

Mesh* Bird::GetHitBoxMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = hitBoxOffsetX;
	offsetY = hitBoxOffsetY;

	return mHitBox;
}


GLvoid Bird::GetHeadRadius(GLfloat& radius)
{
	radius = headRadius;
}

GLvoid Bird::GetBodyRadii(GLfloat& radiusX, GLfloat& radiusY)
{
	radiusX = bodyRadiusX;
	radiusY = bodyRadiusY;
}

const std::vector<std::pair<GLfloat, GLfloat>>& Bird::GetHitBox()
{
	return hitBox;
}

GLfloat Bird::GetHitBoxRadius()
{
	return hitBoxRadiusX;
}
