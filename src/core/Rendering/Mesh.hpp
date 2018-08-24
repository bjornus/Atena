#pragma once

#include <d3d11.h>
#include <d3dx9math.h>

#include <vector>

namespace Atena
{
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXCOLOR color;

		Vertex(const D3DXVECTOR3 & position, const D3DXCOLOR & color)
			:position(position), color(color)
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