#include "Mesh.hpp"

#include "Context.hpp"

#include "../System/Window.hpp"

#include <iostream>

namespace Vawel
{
	Mesh::Mesh(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices)
		:indicesCount(indices.size())
	{
		//Vertex buffer
		D3D11_BUFFER_DESC vBufferDesc;
		ZeroMemory(&vBufferDesc, sizeof(vBufferDesc));
		vBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vBufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
		vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vSubresourceData;
		vSubresourceData.pSysMem = &vertices[0];

		HR(Window::getContext()->device->CreateBuffer(&vBufferDesc, &vSubresourceData, &vertexBuffer));

		//Index buffer
		D3D11_BUFFER_DESC iBufferDesc;
		ZeroMemory(&iBufferDesc, sizeof(iBufferDesc));
		iBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		iBufferDesc.ByteWidth = sizeof(unsigned int) * indices.size();
		iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA iSubresourceData;
		iSubresourceData.pSysMem = &indices[0];

		HR(Window::getContext()->device->CreateBuffer(&iBufferDesc, &iSubresourceData, &indexBuffer));
	}

	Mesh::~Mesh()
	{
		vertexBuffer->Release();
		indexBuffer->Release();
	}

	void Mesh::draw()
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		
		Window::getContext()->deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		Window::getContext()->deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		Window::getContext()->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Window::getContext()->deviceContext->DrawIndexed(indicesCount, 0, 0);
	}
}