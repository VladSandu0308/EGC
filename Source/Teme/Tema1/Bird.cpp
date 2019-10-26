#include "Bird.h"

Bird::Bird() :
	wingDirection(1.f),
	wingSpeed(200.f),
	radius(30.f),
	scale(1.f),
	numTriangles(50)
{
	GLfloat arg;
	wingHeight = 70.f;

	/* Generate the bird's head */
	{
		Mesh* part = new Mesh("head");
		
		vector<VertexFormat> vertices;
		vector<GLushort> indices;

		// TODO: schimba culorile
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

		part->InitFromData(vertices, indices);
		part->SetDrawMode(GL_TRIANGLE_FAN);

		headOffsetX = 35.f;
		headOffsetY = 0.f;
		meshes["head"] = part;
	}

	/* Generate the bird's body */
	{
		Mesh* part = new Mesh("body");

		vector<VertexFormat> vertices;
		vector<GLushort> indices;

		// TODO: schimba culorile
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

		part->InitFromData(vertices, indices);
		part->SetDrawMode(GL_TRIANGLE_FAN);

		bodyOffsetX = -20.f;
		bodyOffsetY = 0.f;
		meshes["body"] = part;
	}

	/* Generate the bird's eye */
	{
		Mesh* part = new Mesh("eye");

		vector<VertexFormat> vertices;
		vector<GLushort> indices;

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

		part->InitFromData(vertices, indices);
		part->SetDrawMode(GL_TRIANGLE_FAN);

		eyeOffsetX = 50.f;
		eyeOffsetY = 10.f;
		meshes["eye"] = part;
	}

	/* Generate the bird's beak */
	{
		Mesh* part = new Mesh("beak");

		vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.941f, 0.627f, 0.298f)),
			VertexFormat(glm::vec3(0.f, -15.f, 0.f), glm::vec3(0.941f, 0.627f, 0.298f)),
			VertexFormat(glm::vec3(30.f, -7.5f, 0.f), glm::vec3(0.941f, 0.627f, 0.298f))
		};
		vector<GLushort> indices =
		{
			0, 1, 2
		};

		part->InitFromData(vertices, indices);

		beakOffsetX = 50.f;
		beakOffsetY = 0.f;
		meshes["beak"] = part;
	}

	/* Generate the bird's tail */
	{
		Mesh* part = new Mesh("tail");

		vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-30.f, 20.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-30.f, -20.f, 0.f), glm::vec3(0.f, 0.f, 1.f))
		};
		vector<GLushort> indices =
		{
			0, 1, 2
		};

		part->InitFromData(vertices, indices);

		tailOffsetX = -50.f;
		tailOffsetY = 0.f;
		meshes["tail"] = part;
	}

	/* Generate the bird's wing */
	{
		Mesh* part = new Mesh("wing");

		vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(.75f, 1.f, 0.f)),
			VertexFormat(glm::vec3(50.f, 0.f, 0.f), glm::vec3(.75f, 1.f, 0.f)),
			VertexFormat(glm::vec3(25.f, wingHeight, 0.f), glm::vec3(.75f, 1.f, 0.f))
		};
		vector<GLushort> indices =
		{
			0, 1, 2
		};

		part->InitFromData(vertices, indices);

		wingOffsetX = -50.f;
		wingOffsetY = 0.f;
		meshes["wing"] = part;
	}
}

void Bird::FlapWing(float deltaTimeSeconds)
{
	wingHeight += wingDirection * deltaTimeSeconds * wingSpeed;

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

	Mesh* part = new Mesh("wing");

	vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(.75f, 1.f, 0.f)),
		VertexFormat(glm::vec3(50.f, 0.f, 0.f), glm::vec3(.75f, 1.f, 0.f)),
		VertexFormat(glm::vec3(25.f, wingHeight, 0.f), glm::vec3(.75f, 1.f, 0.f))
	};
	vector<GLushort> indices =
	{
		0, 1, 2
	};

	part->InitFromData(vertices, indices);
	meshes["wing"] = part;
}

Bird::~Bird()
{
}

Mesh* Bird::getHeadMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = headOffsetX;
	offsetY = headOffsetY;

	return meshes["head"];
}

Mesh* Bird::getBeakMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = beakOffsetX;
	offsetY = beakOffsetY;

	return meshes["beak"];
}

Mesh* Bird::getEyeMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = eyeOffsetX;
	offsetY = eyeOffsetY;

	return meshes["eye"];
}

Mesh* Bird::getWingMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = wingOffsetX;
	offsetY = wingOffsetY;

	return meshes["wing"];
}

Mesh* Bird::getBodyMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = bodyOffsetX;
	offsetY = bodyOffsetY;

	return meshes["body"];
}

Mesh* Bird::getTailMesh(GLfloat& offsetX, GLfloat& offsetY)
{
	offsetX = tailOffsetX;
	offsetY = tailOffsetY;

	return meshes["tail"];
}