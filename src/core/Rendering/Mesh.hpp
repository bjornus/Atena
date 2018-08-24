#pragma once

#include <d3d11.h>
#include <d3dx9math.h>

#include <vector>

#include "../Math.hpp"
#include "../Common.hpp"

namespace Atena
{
	class Context;
	class ATENA_API Mesh
	{
	public:
		Mesh(const std::vector<Vertex> vertices);
		~Mesh();

		void draw();
	private:
		ID3D11Buffer * vertexBuffer;
		ID3D11InputLayout * layout;

		int verticesCount;
	};
}