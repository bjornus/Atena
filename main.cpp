#include <Windows.h>
#include <d3d11.h>
#include <assert.h>
#include <dxgi.h>
#include <d3dx9math.h>
#include <D3DX11async.h>
#include <DxErr.h>

#include "src/core/System/Window.hpp"

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
		#define HR(x)                                              \
		{                                                          \
			HRESULT hr = (x);                                      \
			if(FAILED(hr))                                         \
			{                                                      \
				DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
			}                                                      \
		}
		#endif
#else
	#ifndef HR
		#define HR(x) (x)
	#endif
#endif

D3DXCOLOR color(0.0f, 0.0f, 0.0f, 0.0f);

struct Vertex
{
	float x, y, z;
	D3DXCOLOR color;
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
	Atena::Window window(800, 600);

	//<DX>
	UINT createDeviceFlags = 0;
#if defined(DEBUG) | defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Device * device;
	ID3D11DeviceContext * deviceContext;

	HR(D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &device, &featureLevel, &deviceContext));

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Error D3D11 not available", L"ERROR", 0);
	}

	bool enableMultiSampling = true;

	UINT multiSamplingQuality;
	device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &multiSamplingQuality);
	assert(multiSamplingQuality > 0);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	swapChainDesc.BufferDesc.Width = 800;
	swapChainDesc.BufferDesc.Height = 600;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (enableMultiSampling)
	{
		swapChainDesc.SampleDesc.Count = 4;
		swapChainDesc.SampleDesc.Quality = multiSamplingQuality - 1;
	}
	else
	{
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = windowHandle;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	IDXGIDevice * dxgiDevice = 0;
	HR(device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));
	IDXGIAdapter * dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));
	IDXGIFactory * dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));
	IDXGISwapChain * swapChain;
	HR(dxgiFactory->CreateSwapChain(device, &swapChainDesc, &swapChain));

	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	ID3D11RenderTargetView * renderTargetView;
	ID3D11Texture2D * backBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	device->CreateRenderTargetView(backBuffer, 0, &renderTargetView);
	backBuffer->Release();

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = 800;
	depthStencilDesc.Height = 600;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (enableMultiSampling)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = multiSamplingQuality - 1;
	}
	else
	{

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	ID3D11Texture2D * depthStencilBuffer;
	ID3D11DepthStencilView * depthStencilView;

	HR(device->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer));
	HR(device->CreateDepthStencilView(depthStencilBuffer, 0, &depthStencilView));

	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = 800;
	viewPort.Height = 600;
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1;

	deviceContext->RSSetViewports(1, &viewPort);

	// VertexBuffer

	Vertex vertices[] =
	{
		{ 0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0, 0.0f, 1.0f) },
		{ 0.5f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0, 0.0f, 1.0f) },
		{ -0.5f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f) },
	};

	ID3D11Buffer * vertexBuffer;
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(Vertex) * 3;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HR(device->CreateBuffer(&bufferDesc, NULL, &vertexBuffer));

	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	HR(deviceContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource));
	memcpy(mappedSubresource.pData, vertices, sizeof(vertices));
	deviceContext->Unmap(vertexBuffer, NULL);

	//Shaders
	ID3D11InputLayout * layout;
	ID3D11VertexShader * vertexShader;
	ID3D11PixelShader * pixelShader;
	ID3D10Blob * vertexShaderBlob, *pixelShaderBlob;
	HR(D3DX11CompileFromFile(L"shader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &vertexShaderBlob, 0, 0));
	HR(D3DX11CompileFromFile(L"shader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &pixelShaderBlob, 0, 0));

	HR(device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &vertexShader));
	HR(device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, &pixelShader));

	deviceContext->VSSetShader(vertexShader, 0, 0);
	deviceContext->PSSetShader(pixelShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HR(device->CreateInputLayout(inputElementDesc, 2, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &layout));
	deviceContext->IASetInputLayout(layout);

	//</DX>
	window.run();

	depthStencilBuffer->Release();
	depthStencilView->Release();
	renderTargetView->Release();
	swapChain->Release();
	device->Release();
	deviceContext->Release();

	vertexShader->Release();
	pixelShader->Release();
	layout->Release();
	vertexBuffer->Release();

	return (int)msg.wParam;
}
