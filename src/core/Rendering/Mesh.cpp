#include "Mesh.hpp"

#include "Context.hpp"

#include "../Common.hpp"

namespace Atena
{
	Mesh::Mesh(const std::vector<Vertex> vertices, Context * context)
		:verticesCount(vertices.size()), context(context)
	{
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(Vertex) * 3;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		
		HR(context->device->CreateBuffer(&bufferDesc, NULL, &vertexBuffer));

		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		HR(context->deviceContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource));
		memcpy(mappedSubresource.pData, &vertices[0], sizeof(Vertex) * vertices.size());
		context->deviceContext->Unmap(vertexBuffer, NULL);
	}

	Mesh::~Mesh()
	{
		vertexBuffer->Release();
	}

	void Mesh::draw()
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		
		context->deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->deviceContext->Draw(verticesCount, 0);
	}
}