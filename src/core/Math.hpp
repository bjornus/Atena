#pragma once

#include "Common.hpp"

namespace Wawel
{
	struct WAWEL_API Vector3
	{
		float x, y, z;
	};

	struct WAWEL_API Color
	{
		float r, g, b, a;
	};

	struct WAWEL_API Vertex
	{
		Vector3 position;
		Color color;
	};
}