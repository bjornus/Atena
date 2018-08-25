#pragma once

#include <d3d11.h>
#include <d3dx9math.h>

#include <vector>

#include "../Math.hpp"
#include "../Common.hpp"

namespace Wawel
{
	class Context;
	class WAWEL_API Mesh
	{
	public:
		Mesh(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices);
		~Mesh();

		void draw();
	private:
		ID3D11Buffer * vertexBuffer;
		ID3D11Buffer * indexBuffer;
		
		int indicesCount;
	};
}