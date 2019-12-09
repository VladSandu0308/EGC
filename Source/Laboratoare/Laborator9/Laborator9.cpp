#include "Laborator9.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator9::Laborator9()
{
}

Laborator9::~Laborator9()
{
}

void Laborator9::Init()
{
	const string textureLoc = "Source/Laboratoare/Laborator9/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "grass_bilboard.png").c_str(), GL_REPEAT);
		mapTextures["grass"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "crate.jpg").c_str(), GL_REPEAT);
		mapTextures["crate"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "earth.png").c_str(), GL_REPEAT);
		mapTextures["earth"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D("Resources/Models/Vegetation/Bamboo/bamboo.png", GL_REPEAT);
		mapTextures["bamboo"] = texture;
	}

	{
		mapTextures["random"] = CreateRandomTexture(32, 32);
	}

	// Load meshes
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("bamboo");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Vegetation/Bamboo/", "bamboo.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple quad
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0.5f,   0.5f, 0.0f),	// Top Right
			glm::vec3(0.5f,  -0.5f, 0.0f),	// Bottom Right
			glm::vec3(-0.5f, -0.5f, 0.0f),	// Bottom Left
			glm::vec3(-0.5f,  0.5f, 0.0f),	// Top Left
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0)
		};

		// Texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.f, 0.f),
			glm::vec2(0.f, 1.f),
			glm::vec2(1.f, 1.f),
			glm::vec2(1.f, 0.f)
		};

		vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Mesh* mesh = new Mesh("square");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab9");
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	mixTextures = false;
}

void Laborator9::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

void Laborator9::Update(float deltaTimeSeconds)
{
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 1, -3));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["earth"], nullptr);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab9"], modelMatrix, mapTextures["crate"], nullptr);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(75.0f), glm::vec3(1, 1, 0));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab9"], modelMatrix, mapTextures["random"], nullptr);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.5f, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		
		glm::vec3 oY = glm::mat3(GetSceneCamera()->GetViewMatrix()) * glm::vec3(0.f, 0.f, 1.f);
		GLfloat angle = acos(glm::dot(oY, glm::vec3(0.f, 0.f, 1.f)));
		modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0.f, 1.f, 0.f));
		//modelMatrix = glm::rotate(modelMatrix, GetSceneCamera()->transform->GetRotationEulerRad().y, glm::vec3(0.f, 1.f, 0.f));
		
		mixTextures = true;
		RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"], mapTextures["earth"]);
		mixTextures = false;
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, -0.5f, -3));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderSimpleMesh(meshes["bamboo"], shaders["ShaderLab9"], modelMatrix, mapTextures["bamboo"], nullptr);
	}
}

void Laborator9::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator9::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// BONUS: Deciding wether to rotate the mesh or not
	GLint locTime		= glGetUniformLocation(shader->program, "time");
	GLboolean isQuad	= false;

	if (mesh == meshes["square"])
	{
		isQuad = true;
	}

	GLint locIsQuad = glGetUniformLocation(shader->program, "is_quad");
	glUniform1i(locIsQuad, isQuad);

	if (mesh == meshes["sphere"])
	{
		glUniform1f(locTime, (GLfloat)Engine::GetElapsedTime());
	} else
	{
		glUniform1f(locTime, -1.f);
	}

	glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), mixTextures);

	if (texture1)
	{
		// Activate texture location 0
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		// Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	if (texture2)
	{
		// Activate texture location 1
		glActiveTexture(GL_TEXTURE1);

		// Bind the texture2 ID
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

		// Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

Texture2D* Laborator9::CreateRandomTexture(unsigned int width, unsigned int height)
{
	unsigned int channels	= 3;
	unsigned int size		= width * height * channels;
	unsigned char* data		= new unsigned char[size];

	// Generate random texture data
	for (size_t i = 0; i < size; ++i)
	{
		data[i] = rand() % (UINT8_MAX + 1);
	}

	// Generate and bind the new texture ID
	glGenTextures(1, &randomTextureID);
	glBindTexture(GL_TEXTURE_2D, randomTextureID);

	// Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	CheckOpenGLError();

	// Use glTextImage2D to set the texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// Generate texture mip-maps
	glGenerateMipmap(GL_TEXTURE_2D);
	CheckOpenGLError();

	// Save the texture into a wrapper Texture2D class for using easier later during rendering phase
	Texture2D* texture = new Texture2D();
	texture->Init(randomTextureID, width, height, channels);

	SAFE_FREE_ARRAY(data);
	return texture;
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator9::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	}
}

void Laborator9::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator9::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator9::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator9::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator9::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator9::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator9::OnWindowResize(int width, int height)
{
}
