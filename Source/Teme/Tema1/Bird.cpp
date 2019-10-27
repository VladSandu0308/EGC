#include "Bird.h"

Bird::Bird() :
	wingDirection(1.f),
	wingSpeed(200.f),
	radius(30.f),
	scale(1.f),
	numTriangles(50),
	wingAcceleration(30.f)
{
	GLfloat arg;
	wingHeight = 70.f;

	/* Generate the bird's head */
	{
		mHead = new Mesh("head");
		
		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;

		vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.811f, 0.188f, 0.517f));

		for (GLushort i = 0; i < numTriangles; ++i)
		{
			arg = 2.0f * (GLfloat)M_PI * i / numTriangles;

			vertices.emplace_back(
				glm::vec3(cos(arg) * radius * .75f, sin(arg) * radius * .75f, 0),
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
			glm::vec3(0.635f, 0.086f, 0.376f));

		for (GLushort i = 0; i < numTriangles; ++i)
		{
			arg = 2.0f * (GLfloat)M_PI * i / numTriangles;

			vertices.emplace_back(
				glm::vec3(cos(arg) * radius * 1.5f, sin(arg) * radius, 0),
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
				glm::vec3(cos(arg) * radius / 4.f, sin(arg) * radius / 4.f, 0),
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
			VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.941f, 0.627f, 0.298f)),
			VertexFormat(glm::vec3(0.f, -15.f, 0.f), glm::vec3(0.941f, 0.627f, 0.298f)),
			VertexFormat(glm::vec3(30.f, -7.5f, 0.f), glm::vec3(0.941f, 0.627f, 0.298f))
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
			VertexFormat(glm::vec3(-30.f, 20.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-30.f, -20.f, 0.f), glm::vec3(0.f, 0.f, 1.f))
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
			VertexFormat(glm::vec3(25.f, wingHeight, 0.f), glm::vec3(.75f, 1.f, 0.f))
		};
		std::vector<GLushort> indices =
		{
			0, 1, 2
		};

		mWing->InitFromData(vertices, indices);

		wingOffsetX = -50.f;
		wingOffsetY = 0.f;
	}
}

void Bird::FlapWing(GLfloat deltaTimeSeconds)
{
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

Mesh* Bird::getHeadMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = headOffsetX;
	offsetY = headOffsetY;

	return mHead;
}

Mesh* Bird::getBeakMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = beakOffsetX;
	offsetY = beakOffsetY;

	return mBeak;
}

Mesh* Bird::getEyeMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = eyeOffsetX;
	offsetY = eyeOffsetY;

	return mEye;
}

Mesh* Bird::getWingMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = wingOffsetX;
	offsetY = wingOffsetY;

	return mWing;
}

Mesh* Bird::getBodyMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = bodyOffsetX;
	offsetY = bodyOffsetY;

	return mBody;
}

Mesh* Bird::getTailMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = tailOffsetX;
	offsetY = tailOffsetY;

	return mTail;
}