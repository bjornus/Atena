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
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(Vertex) * 3;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		
		HR(Window::getContext()->device->CreateBuffer(&bufferDesc, NULL, &vertexBuffer));

		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		HR(Window::getContext()->deviceContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource));
		memcpy(mappedSubresource.pData, &vertices[0], sizeof(Vertex) * vertices.size());
		Window::getContext()->deviceContext->Unmap(vertexBuffer, NULL);
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