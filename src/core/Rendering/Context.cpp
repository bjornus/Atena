#include "Context.hpp"

#include <d3dx9math.h>

#include <assert.h>

namespace Atena
{
	Context::Context(HWND windowHandle, const int & width, const int & height, const bool & vSync, const bool & antialiasing)
		:vSync(vSync), antialiasing(antialiasing)
	{
		UINT createDeviceFlags = 0;
#if defined(DEBUG) | defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featureLevel;

		HR(D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &device, &featureLevel, &deviceContext));

		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(0, L"Error D3D11 not available", L"ERROR", 0);
		}

		UINT multiSamplingQuality;
		device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &multiSamplingQuality);
		assert(multiSamplingQuality > 0);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (antialiasing)
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
		HR(dxgiFactory->CreateSwapChain(device, &swapChainDesc, &swapChain));

		dxgiDevice->Release();
		dxgiAdapter->Release();
		dxgiFactory->Release();

		ID3D11Texture2D * backBuffer;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
		device->CreateRenderTargetView(backBuffer, 0, &renderTargetView);
		backBuffer->Release();

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		if (antialiasing)
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

		HR(device->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer));
		HR(device->CreateDepthStencilView(depthStencilBuffer, 0, &depthStencilView));
		depthStencilBuffer->Release();

		deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

		D3D11_VIEWPORT viewPort;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		viewPort.Width = width;
		viewPort.Height = height;
		viewPort.MinDepth = 0;
		viewPort.MaxDepth = 1;

		deviceContext->RSSetViewports(1, &viewPort);
	}

	Context::~Context()
	{
		device->Release();
		swapChain->Release();
		deviceContext->Release();
		depthStencilView->Release();
		renderTargetView->Release();
	}

	void Context::clear() const
	{
		deviceContext->ClearRenderTargetView(renderTargetView, D3DXCOLOR(0.35, 0.35, 0.35, 1));
		deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0.0);
	}

	void Context::present() const
	{
		HR(swapChain->Present(vSync, 0));
	}

	void Context::setVsync(const bool & vSync)
	{
		this->vSync = vSync;
	}
	void Context::setAntialiasing(const bool & antialiasing)
	{
		this->antialiasing = antialiasing;
	}
}