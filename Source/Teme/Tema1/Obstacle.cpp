#include "Obstacle.h"

Obstacle::Obstacle(GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b)
{
	mObstacle = new Mesh("Obstacle" + std::to_string(r));

	/* Vertices for the obstacle */
	/*std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0.f,		0.f,	0.f), glm::vec3(r, g, b)),
		VertexFormat(glm::vec3(width,	0.f,	0.f), glm::vec3(r, g, b)),
		VertexFormat(glm::vec3(width,	height, 0.f), glm::vec3(1.f, 1.f, 1.f)),
		VertexFormat(glm::vec3(0.f,		height, 0.f), glm::vec3(1.f, 1.f, 1.f))
	};*/

	std::vector<glm::vec3> vertices
	{
		glm::vec3(0.f,		0.f,	0.f),
		glm::vec3(width,	0.f,	0.f),
		glm::vec3(width,	height, 0.f),
		glm::vec3(0.f,		height, 0.f)
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(0.f, 1.f, 1.f),
		glm::vec3(1.f, 0.f, 1.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f)
	};

	// Texture coordinates for the square
	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0.f, 0.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(0.f, 1.f)
	};

	/* Indices for the obstacle */
	std::vector<GLushort> indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	mObstacle->InitFromData(vertices, normals, textureCoords, indices);
}

Obstacle::~Obstacle()
{
}

Mesh* Obstacle::GetMesh()
{
	return mObstacle;
}