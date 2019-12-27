#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>

class WormsUtils
{
public:
	/* Creates a mesh with the given vertices, indices and name */
	static Mesh* CreateMesh(
		const GLchar* name,
		const std::vector<VertexFormat>& vertices,
		const std::vector<GLushort>& indices
	);

private:
	WormsUtils() = default;
	~WormsUtils() = default;

	virtual void abstractize() = 0;
};