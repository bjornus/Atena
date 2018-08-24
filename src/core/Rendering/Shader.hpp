#pragma once

#include "Context.hpp"

#include <d3d11.h>

#include <string>

namespace Atena
{
	class Shader
	{
	public:
		Shader(const std::string & filepath, Context * context);
		~Shader();

		void bind();
	private:
		Context * context;

		ID3D11VertexShader * vertexShader;
		ID3D11PixelShader * pixelShader;
	};
}