#pragma once

#include <d3d11.h>

#include "../Common.hpp"

namespace Vawel
{
	class VAWEL_API Context
	{
	public:
		Context(HWND windowHandle, const int & width, const int & height, const bool & vSync = false, const bool & antialiasing = false);
		~Context();

		void clear() const;
		void present() const;

		void setVsync(const bool & vSync);
		void setAntialiasing(const bool & antialiasing);
	private:
		bool vSync;
		bool antialiasing;

		ID3D11Device * device;
		IDXGISwapChain * swapChain;
		ID3D11DeviceContext * deviceContext;
		ID3D11DepthStencilView * depthStencilView;
		ID3D11RenderTargetView * renderTargetView;

		friend class Mesh;
		friend class Shader;
	};
}