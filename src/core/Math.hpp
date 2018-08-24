#pragma once

#include "Common.hpp"

namespace Atena
{
	struct ATENA_API Vector3
	{
		float x, y, z;
	};

	struct ATENA_API Color
	{
		float r, g, b, a;
	};

	struct ATENA_API Vertex
	{
		Vector3 position;
		Color color;
	};
}