#include "Laborator2.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator2::Laborator2()
{
}

Laborator2::~Laborator2()
{

}

void Laborator2::Init()
{
	cullFace = GL_FRONT;
	polygonMode = GL_FILL;

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a mesh box using custom data
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(.5f, .5f, 1.f)),
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1.f, .5f, 1.f)),
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(.5f, 1.f, 1.f)),
			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(.75f, .25f, .25f)),
			VertexFormat(glm::vec3(0, 0, 1), glm::vec3(1.f, .5f, .5f)),
			VertexFormat(glm::vec3(1, 0, 1), glm::vec3(.25f, .75f, .75f)),
			VertexFormat(glm::vec3(1, 1, 1), glm::vec3(1.f, 1.f, .5f)),
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(.5f, 1.f, .5f))
		};

		vector<GLushort> indices =
		{
			0, 5, 1,	// indices for first triangle
			0, 4, 5,	// indices for second triangle
			0, 7, 4,	// etc.
			0, 3, 7,
			3, 6, 7,
			3, 2, 6,
			2, 5, 6,
			2, 1, 5,
			0, 1, 2,
			0, 2, 3,
			4, 6, 5,
			4, 7, 6
		};

		meshes["cube1"] = new Mesh("generated cube 1");
		meshes["cube1"]->InitFromData(vertices, indices);

		// Create a new mesh from buffer data
		CreateMesh("cube3", vertices, indices);
	}

	// Create a tetrahedron mesh using vertices and indices
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(.5f, .5f, 1.f)),
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1.f, .5f, 1.f)),
			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(.75f, .25f, .25f)),
			VertexFormat(glm::vec3(0, 0, 1), glm::vec3(1.f, .5f, .5f))
		};

		vector<GLushort> indices =
		{
			0, 3, 1,	// indices for first triangle
			0, 1, 2,	// indices for second triangle
			0, 2, 3,	// etc.
			1, 3, 2
		};

		// Create a new mesh from buffer data
		CreateMesh("tetrahedron", vertices, indices);
	}

	// Create a sqare mesh using vertices and indices
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1.f, 0.f, 0.f)),
			VertexFormat(glm::vec3(0, 1, 0)),
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0.f, 0.f, 1.f)),
			VertexFormat(glm::vec3(0, 0, 1))
		};

		vector<GLushort> indices =
		{
			0, 3, 1,	// indices for first triangle
			1, 2, 3		// indices for second triangle
		};

		// Create a new mesh from buffer data
		CreateMesh("square", vertices, indices);
	}

	// BONUS: Create a circle mesh using vertices and indices
	{
		vector<VertexFormat> vertices;
		vector<GLushort> indices;
		GLfloat arg;

		vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(1.f, 1.f, 1.f));
		for (GLushort i = 0; i < NUM_TRIANGLES; i++)
		{
			arg = TWO_PI * i / NUM_TRIANGLES;

			vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), glm::vec3(1.f, 1.f, 0.f));
			indices.push_back(i);
		}
		indices.push_back(NUM_TRIANGLES);
		indices.push_back(1);

		// Create a new mesh from buffer data
		CreateMesh("circle", vertices, indices);
		meshes["circle"]->SetDrawMode(GL_TRIANGLE_FAN);
	}
}

Mesh* Laborator2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	// Create the VAO and bind it
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	GLuint VBO = 0;
	glGenBuffers(1, &VBO);

	// Send vertices data into the VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	GLuint IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);


	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	
	return meshes[name];
}

void Laborator2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// Enable face culling
	glEnable(GL_CULL_FACE);

	// Set face custom culling. Use the "cullFace" variable
	glCullFace(cullFace);

	// Render an object using face normals for color
	RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -1.5f), glm::vec3(0.75f));

	// Render an object using colors from vertex
	RenderMesh(meshes["cube1"], shaders["VertexColor"], glm::vec3(-1.5f, 0.5f, 0.f)); // cube generated with InitFromData
	RenderMesh(meshes["cube3"], shaders["VertexColor"], glm::vec3(1.5f, 0.5f, 0.f)); // the same cube generated with VAO, VBO, IBO

	RenderMesh(meshes["tetrahedron"], shaders["VertexColor"], glm::vec3(0.f, 2.f, -1.5f)); // tetrahedron generated with VAO, VBO, IBO

	RenderMesh(meshes["square"], shaders["VertexColor"], glm::vec3(0.f, 3.f, 0.f));

	RenderMesh(meshes["circle"], shaders["VertexColor"], glm::vec3(0.f, 2.f, 1.5f));

	// Disable face culling
	glDisable(GL_CULL_FACE);
}

void Laborator2::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator2::OnInputUpdate(float deltaTime, int mods)
{

}

void Laborator2::OnKeyPress(int key, int mods)
{
	// Switch between GL_FRONT and GL_BACK culling
	// Save the state in "cullFace" variable and apply it in the Update() method not here
	if (key == GLFW_KEY_F2)
	{
		cullFace = cullFace ^ GL_BACK ^ GL_FRONT;
	}

	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Laborator2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator2::OnWindowResize(int width, int height)
{
}
