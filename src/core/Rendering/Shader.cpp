#include "Shader.hpp"

#include "../System/Window.hpp"

#include <D3DX11async.h>

namespace Atena
{
	Shader::Shader(const std::string & filepath)
	{
		ID3D10Blob * vertexShaderBlob, *pixelShaderBlob;
		HR(D3DX11CompileFromFile(L"shader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &vertexShaderBlob, 0, 0));
		HR(D3DX11CompileFromFile(L"shader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &pixelShaderBlob, 0, 0));

		HR(Window::getContext()->device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &vertexShader));
		HR(Window::getContext()->device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, &pixelShader));

		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		
		HR(Window::getContext()->device->CreateInputLayout(inputElementDesc, 2, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &layout));
		
		vertexShaderBlob->Release();
		pixelShaderBlob->Release();
	}

	Shader::~Shader()
	{
		vertexShader->Release();
		pixelShader->Release();
		layout->Release();
	}

	void Shader::bind()
	{
		Window::getContext()->deviceContext->IASetInputLayout(layout);
		Window::getContext()->deviceContext->VSSetShader(vertexShader, 0, 0);
		Window::getContext()->deviceContext->PSSetShader(pixelShader, 0, 0);
	}
}