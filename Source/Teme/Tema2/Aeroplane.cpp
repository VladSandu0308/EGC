#include "Aeroplane.h"

Aeroplane::Aeroplane() :
	offsetPropellerX(3.175f),	offsetPropellerY(0.f),	offsetPropellerZ(0.f),
	offsetNoseX(2.875f),		offsetNoseY(0.f),		offsetNoseZ(0.f),
	offsetBodyX(1.175f),		offsetBodyY(0.f),		offsetBodyZ(0.f),
	offsetCockpitX(1.175f),		offsetCockpitY(1.25f),	offsetCockpitZ(0.f),
	offsetTailX(-1.825f),		offsetTailY(0.f),		offsetTailZ(0.f),
	offsetWingX(-.175f),		offsetWingY(0.f),		offsetWingZ(1.f),
	offsetRudderX(-3.275f),		offsetRudderY(0.f),		offsetRudderZ(0.f),
	offsetRudderWingX(-3.275f),	offsetRudderWingY(0.f), offsetRudderWingZ(.5f),
	offsetLightX(-4.5f),		offsetLightY(2.f),		offsetLightZ(0.f),
	fmmx(-4.5f),				fmmy(0.f),				fmmz(0.f)
{
	/* Create the plane's propeller */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.1f, -1.2f, .2f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(.1f, -1.2f, .2f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-0.1f, 1.2f, .2f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(.1f, 1.2f, .2f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(-0.1f, -1.2f, -.2f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(.1f, -1.2f, -.2f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(-0.1f, 1.2f, -.2f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(.1f, 1.2f, -.2f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
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

		propeller = Utils::CreateMesh("propeller", vertices, indices);
	}

	/* Create the plane's nose */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-.2f, -.2f, .2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(.2f, -.2f, .2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-.2f, .2f, .2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(.2f, .2f, .2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(-.2f, -.2f, -.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(.2f, -.2f, -.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(-.2f, .2f, -.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(.2f, .2f, -.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f))
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

		nose = Utils::CreateMesh("nose", vertices, indices);
	}

	/* Create the plane's body */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1.5f, -1.f,  1.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -1.f,  1.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-1.5f,  1.f,  1.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f,  1.f,  1.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(-1.5f, -1.f, -1.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -1.f, -1.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(-1.5f,  1.f, -1.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(1.5f,  1.f, -1.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 1.f))
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

		body = Utils::CreateMesh("body", vertices, indices);
	}

	/* Create the plane's cockpit */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1.f, -.5f, .5f), glm::vec3(.659f, .8f, .843f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.f, -.5f, .5f), glm::vec3(.659f, .8f, .843f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-1.f, .5f, .5f), glm::vec3(.659f, .8f, .843f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.f, .5f, .5f), glm::vec3(.659f, .8f, .843f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(-1.f, -.5f, -.5f), glm::vec3(.659f, .8f, .843f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.f, -.5f, -.5f), glm::vec3(.659f, .8f, .843f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(-1.f, .5f, -.5f), glm::vec3(.659f, .8f, .843f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(1.f, .5f, -.5f), glm::vec3(.659f, .8f, .843f), glm::vec3(0.f, 0.f, 1.f))
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

		cockpit = Utils::CreateMesh("cockpit", vertices, indices);
	}

	/* Create the plane's tail */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1.5f, -.5f, .5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -1.f, 1.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(-1.5f, .5f, .5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, 1.f, 1.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(-1.5f, -.5f, -.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -1.f, -1.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(-1.5f, .5f, -.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, 1.f, -1.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f))
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

		tail = Utils::CreateMesh("tail", vertices, indices);
	}

	/* Create the plane's rudder */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0.f, 0.f, .1f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, 0.f, .1f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0.f, 2.f, .1f), glm::vec3(1.f, 1.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(.75f, 2.f, .1f), glm::vec3(1.f, 1.f, 0.f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(0.f, 0.f, -.1f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, 0.f, -.1f), glm::vec3(1.f, 1.f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(0.f, 2.f, -.1f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(.75f, 2.f, -.1f), glm::vec3(1.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
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

		rudder = Utils::CreateMesh("rudder", vertices, indices);
	}

	/* Create the plane's wing */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(1.5f, -.1f, 3.f), glm::vec3(.612f, .102f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(2.f, -.1f, 3.f), glm::vec3(.612f, .102f, 0.f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, .1f, 3.f), glm::vec3(.612f, .102f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(2.f, .1f, 3.f), glm::vec3(.612f, .102f, 0.f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(0.f, -.1f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(2.f, -.1f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(0.f, .1f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(2.f, .1f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 1.f))
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

		wing = Utils::CreateMesh("wing", vertices, indices);
	}

	/* Create the plane's rudder wing */
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(1.f, -.1f, 1.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -.1f, 1.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(1.f, .1f, 1.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, .1f, 1.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(0.f, -.1f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(1.5f, -.1f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 1.f)),
			VertexFormat(glm::vec3(0.f, .1f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 0.f)),
			VertexFormat(glm::vec3(1.5f, .1f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f))
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

		rudderWing = Utils::CreateMesh("rudderWing", vertices, indices);
	}

	{
		light = new Mesh("light");
		light->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");

		fmm = new Mesh("fmm");
		fmm->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	}

	{
		shader = new Shader("PlaneShader");
		shader->AddShader("Source/Teme/Tema2/Shaders/PlaneVertex.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Teme/Tema2/Shaders/PlaneFragment.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
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
	delete light;
	delete shader;
}

GLvoid Aeroplane::GetBBoxOffsets(
	GLfloat& deltaXRight,
	GLfloat& deltaXLeft,
	GLfloat& deltaYUp,
	GLfloat& deltaYDown
)
{
	deltaXRight	= 3.275f;
	deltaXLeft	= -3.275f;
	deltaYUp	= 1.75f;
	deltaYDown	= -1.f;
}

Mesh* Aeroplane::GetPropeller(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = offsetPropellerX;
	offsetY = offsetPropellerY;
	offsetZ = offsetPropellerZ;

	return propeller;
}

Mesh* Aeroplane::GetNose(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = offsetNoseX;
	offsetY = offsetNoseY;
	offsetZ = offsetNoseZ;

	return nose;
}

Mesh* Aeroplane::GetBody(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = offsetBodyX;
	offsetY = offsetBodyY;
	offsetZ = offsetBodyZ;

	return body;
}

Mesh* Aeroplane::GetCockpit(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = offsetCockpitX;
	offsetY = offsetCockpitY;
	offsetZ = offsetCockpitZ;

	return cockpit;
}

Mesh* Aeroplane::GetTail(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = offsetTailX;
	offsetY = offsetTailY;
	offsetZ = offsetTailZ;

	return tail;
}

Mesh* Aeroplane::GetWing(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = offsetWingX;
	offsetY = offsetWingY;
	offsetZ = offsetWingZ;

	return wing;
}

Mesh* Aeroplane::GetRudder(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = offsetRudderX;
	offsetY = offsetRudderY;
	offsetZ = offsetRudderZ;

	return rudder;
}

Mesh* Aeroplane::GetRudderWing(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = offsetRudderWingX;
	offsetY = offsetRudderWingY;
	offsetZ = offsetRudderWingZ;

	return rudderWing;
}

Mesh* Aeroplane::GetLight(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = offsetLightX;
	offsetY = offsetLightY;
	offsetZ = offsetLightZ;

	return light;
}

Mesh* Aeroplane::fmmm(
	GLfloat& offsetX,
	GLfloat& offsetY,
	GLfloat& offsetZ
)
{
	offsetX = fmmx;
	offsetY = fmmy;
	offsetZ = fmmz;

	return fmm;
}

Shader* Aeroplane::GetShader()
{
	return shader;
}