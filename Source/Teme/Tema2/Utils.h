#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>

class Utils
{
public:
	/* Creates a mesh with the given vertices, indices and name */
	static Mesh* CreateMesh(
		const GLchar* name,
		const std::vector<VertexFormat>& vertices,
		const std::vector<GLushort>& indices
	);

	static Mesh* CreateSeaMesh(
		std::string name,
		const std::vector<VertexFormat>& vertices,
		const std::vector<GLushort>& indices
	);

private:
	Utils() = default;
	~Utils() = default;

	virtual void abstractize() = 0;
};