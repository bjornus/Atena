#include "Mesh.hpp"

#include "Context.hpp"

#include "../System/Window.hpp"

#include <iostream>

namespace Atena
{
	Mesh::Mesh(const std::vector<Vertex> vertices)
		:verticesCount(vertices.size())
	{
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		bufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subresourceData;
		subresourceData.pSysMem = &vertices[0];

		HR(Window::getContext()->device->CreateBuffer(&bufferDesc, &subresourceData, &vertexBuffer));
	}

	Mesh::~Mesh()
	{
		vertexBuffer->Release();
	}

	void Mesh::draw()
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		
		Window::getContext()->deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		Window::getContext()->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Window::getContext()->deviceContext->Draw(verticesCount, 0);
	}
}