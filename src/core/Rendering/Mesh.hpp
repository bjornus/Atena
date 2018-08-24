#pragma once

#include <d3d11.h>
#include <d3dx9math.h>

#include <vector>

#include "../Common.hpp"

namespace Atena
{
	struct Vec3
	{
		float x, y, z;
	};

	struct Color
	{
		float r, g, b, a;
	};

	struct ATENA_API Vertex
	{
		Vec3 position;
		Color color;

		Vertex(const Vec3 & position, const Color & color)
			:position(position), color(color)
		{}
	};

	class Context;
	class ATENA_API Mesh
	{
	public:
		Mesh(const std::vector<Vertex> vertices, Context * context);
		~Mesh();

		void draw();
	private:
		ID3D11Buffer * vertexBuffer;
		ID3D11InputLayout * layout;
		Context * context;

		int verticesCount;
	};
}