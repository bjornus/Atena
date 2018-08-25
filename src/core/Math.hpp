#pragma once

#include "Common.hpp"

namespace Vawel
{
	struct VAWEL_API Vector3
	{
		float x, y, z;
	};

	struct VAWEL_API Color
	{
		float r, g, b, a;
	};

	struct VAWEL_API Vertex
	{
		Vector3 position;
		Color color;
	};
}