#pragma once

#include <d3d11.h>
#include <d3dx9math.h>

#include <vector>

namespace Atena
{
	struct Vertex
	{
		float x, y, z;
		D3DXCOLOR color;

		Vertex(const float & x, const float & y, const float & z, const D3DXCOLOR & color)
			:x(x), y(y), z(z), color(color)
		{}
	};

	class Context;
	class Mesh
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