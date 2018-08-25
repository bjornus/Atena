#pragma once

#include "Context.hpp"

#include "../Common.hpp"

#include <d3d11.h>

#include <string>

namespace Wawel
{
	class WAWEL_API Shader
	{
	public:
		Shader(const std::string & filepath);
		~Shader();

		void bind();
	private:
		ID3D11VertexShader * vertexShader;
		ID3D11PixelShader * pixelShader;
		ID3D11InputLayout * layout;
	};
}