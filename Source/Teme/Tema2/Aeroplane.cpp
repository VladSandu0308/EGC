#include "Aeroplane.h"

Aeroplane::Aeroplane() :
	offsetPropellerX(3.f),		offsetPropellerY(0.f),	offsetPropellerZ(0.f),
	offsetNoseX(2.7f),			offsetNoseY(0.f),		offsetNoseZ(0.f),
	offsetBodyX(1.f),			offsetBodyY(0.f),		offsetBodyZ(0.f),
	offsetCockpitX(1.f),		offsetCockpitY(1.25f),	offsetCockpitZ(0.f),
	offsetTailX(-2.f),			offsetTailY(0.f),		offsetTailZ(0.f),
	offsetWingX(0.f),			offsetWingY(0.f),		offsetWingZ(1.f),
	offsetRudderX(-3.45f),		offsetRudderY(0.f),		offsetRudderZ(0.f),
	offsetRudderWingX(-3.45f),	offsetRudderWingY(0.f), offsetRudderWingZ(.5f)
{
	// TODO: culori...

	/* Create the plane's propeller */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.1f, -1.2f, .2f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(.1f, -1.2f, .2f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.1f, 1.2f, .2f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(.1f, 1.2f, .2f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.1f, -1.2f, -.2f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(.1f, -1.2f, -.2f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(-0.1f, 1.2f, -.2f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(.1f, 1.2f, -.2f), glm::vec3(0.f, 0.f, 0.f)),
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		propeller = CreateMesh("propeller", vertices, indices);
	}

	/* Create the plane's nose */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-.2f, -.2f, .2f), glm::vec3(0.5f, 0.5f, 0.5f)),
			VertexFormat(glm::vec3(.2f, -.2f, .2f), glm::vec3(0.5f, 0.5f, 0.5f)),
			VertexFormat(glm::vec3(-.2f, .2f, .2f), glm::vec3(0.5f, 0.5f, 0.5f)),
			VertexFormat(glm::vec3(.2f, .2f, .2f), glm::vec3(0.5f, 0.5f, 0.5f)),
			VertexFormat(glm::vec3(-.2f, -.2f, -.2f), glm::vec3(0.5f, 0.5f, 0.5f)),
			VertexFormat(glm::vec3(.2f, -.2f, -.2f), glm::vec3(0.5f, 0.5f, 0.5f)),
			VertexFormat(glm::vec3(-.2f, .2f, -.2f), glm::vec3(0.5f, 0.5f, 0.5f)),
			VertexFormat(glm::vec3(.2f, .2f, -.2f), glm::vec3(0.5f, 0.5f, 0.5f))
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		nose = CreateMesh("nose", vertices, indices);
	}

	/* Create the plane's body */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1.5f, -1.f,  1.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -1.f,  1.f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-1.5f,  1.f,  1.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f,  1.f,  1.f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(-1.5f, -1.f, -1.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -1.f, -1.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(-1.5f,  1.f, -1.f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(1.5f,  1.f, -1.f), glm::vec3(0.f, 0.f, 1.f))
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		body = CreateMesh("body", vertices, indices);
	}

	/* Create the plane's cockpit */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1.f, -.5f, .5f), glm::vec3(.659f, .8f, .843f)),
			VertexFormat(glm::vec3(1.f, -.5f, .5f), glm::vec3(.659f, .8f, .843f)),
			VertexFormat(glm::vec3(-1.f, .5f, .5f), glm::vec3(.659f, .8f, .843f)),
			VertexFormat(glm::vec3(1.f, .5f, .5f), glm::vec3(.659f, .8f, .843f)),
			VertexFormat(glm::vec3(-1.f, -.5f, -.5f), glm::vec3(.659f, .8f, .843f)),
			VertexFormat(glm::vec3(1.f, -.5f, -.5f), glm::vec3(.659f, .8f, .843f)),
			VertexFormat(glm::vec3(-1.f, .5f, -.5f), glm::vec3(.659f, .8f, .843f)),
			VertexFormat(glm::vec3(1.f, .5f, -.5f), glm::vec3(.659f, .8f, .843f))
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		cockpit = CreateMesh("cockpit", vertices, indices);
	}

	/* Create the plane's tail */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1.5f, -.5f, .5f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -1.f, 1.f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-1.5f, .5f, .5f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, 1.f, 1.f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(-1.5f, -.5f, -.5f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -1.f, -1.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(-1.5f, .5f, -.5f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, 1.f, -1.f), glm::vec3(0.f, 0.f, 1.f))
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		tail = CreateMesh("tail", vertices, indices);
	}

	/* Create the plane's rudder */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0.f, 0.f, .1f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, 0.f, .1f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.f, 2.f, .1f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(.75f, 2.f, .1f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(0.f, 0.f, -.1f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, 0.f, -.1f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(0.f, 2.f, -.1f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(.75f, 2.f, -.1f), glm::vec3(1.f, 1.f, 0.f)),
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		rudder = CreateMesh("rudder", vertices, indices);
	}

	/* Create the plane's wing */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(1.5f, -.1f, 3.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(2.f, -.1f, 3.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, .1f, 3.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(2.f, .1f, 3.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.f, -.1f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(2.f, -.1f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.f, .1f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(2.f, .1f, 0.f), glm::vec3(0.f, 0.f, 0.f))
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		wing = CreateMesh("wing", vertices, indices);
	}

	/* Create the plane's rudder wing */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(1.f, -.1f, 1.5f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, -.1f, 1.5f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.f, .1f, 1.5f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, .1f, 1.5f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.f, -.1f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, -.1f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0.f, .1f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, .1f, 0.f), glm::vec3(0.f, 0.f, 0.f))
		};

		std::vector<GLushort> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		rudderWing = CreateMesh("rudderWing", vertices, indices);
	}
}

Aeroplane::~Aeroplane()
{
	delete propeller;
	delete nose;
	delete body;
	delete cockpit;
	delete tail;
	delete wing;
	delete rudder;
	delete rudderWing;
}

Mesh* Aeroplane::CreateMesh(
	const GLchar* name,
	const std::vector<VertexFormat>& vertices,
	const std::vector<GLushort>& indices)
{
	unsigned int VAO = 0;
	// Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// Set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// Set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// Set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// Set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	Mesh* mesh = new Mesh(name);
	mesh->InitFromBuffer(VAO, static_cast<GLushort>(indices.size()));
	mesh->vertices = vertices;
	mesh->indices = indices;
	
	return mesh;
}

Mesh* Aeroplane::GetPropeller(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ)
{
	offsetX = offsetPropellerX;
	offsetY = offsetPropellerY;
	offsetZ = offsetPropellerZ;

	return propeller;
}

Mesh* Aeroplane::GetNose(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ)
{
	offsetX = offsetNoseX;
	offsetY = offsetNoseY;
	offsetZ = offsetNoseZ;

	return nose;
}

Mesh* Aeroplane::GetBody(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ)
{
	offsetX = offsetBodyX;
	offsetY = offsetBodyY;
	offsetZ = offsetBodyZ;

	return body;
}

Mesh* Aeroplane::GetCockpit(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ)
{
	offsetX = offsetCockpitX;
	offsetY = offsetCockpitY;
	offsetZ = offsetCockpitZ;

	return cockpit;
}

Mesh* Aeroplane::GetTail(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ)
{
	offsetX = offsetTailX;
	offsetY = offsetTailY;
	offsetZ = offsetTailZ;

	return tail;
}

Mesh* Aeroplane::GetWing(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ)
{
	offsetX = offsetWingX;
	offsetY = offsetWingY;
	offsetZ = offsetWingZ;

	return wing;
}

Mesh* Aeroplane::GetRudder(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ)
{
	offsetX = offsetRudderX;
	offsetY = offsetRudderY;
	offsetZ = offsetRudderZ;

	return rudder;
}

Mesh* Aeroplane::GetRudderWing(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ)
{
	offsetX = offsetRudderWingX;
	offsetY = offsetRudderWingY;
	offsetZ = offsetRudderWingZ;

	return rudderWing;
}