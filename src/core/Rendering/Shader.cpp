#include "Shader.hpp"

#include <D3DX11async.h>

namespace Atena
{
	Shader::Shader(const std::string & filepath, Context * context)
		:context(context)
	{
		ID3D10Blob * vertexShaderBlob, *pixelShaderBlob;
		HR(D3DX11CompileFromFile(L"shader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &vertexShaderBlob, 0, 0));
		HR(D3DX11CompileFromFile(L"shader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &pixelShaderBlob, 0, 0));

		HR(context->device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &vertexShader));
		HR(context->device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, &pixelShader));

		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		ID3D11InputLayout * layout;
		HR(context->device->CreateInputLayout(inputElementDesc, 2, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &layout));
		context->deviceContext->IASetInputLayout(layout);

		layout->Release();
		vertexShaderBlob->Release();
		pixelShaderBlob->Release();
	}

	Shader::~Shader()
	{
		vertexShader->Release();
		pixelShader->Release();
	}

	void Shader::bind()
	{
		context->deviceContext->VSSetShader(vertexShader, 0, 0);
		context->deviceContext->PSSetShader(pixelShader, 0, 0);
	}
}