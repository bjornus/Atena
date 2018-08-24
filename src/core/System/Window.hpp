#pragma once

#include "../Rendering/Context.hpp"

#include "../Common.hpp"

#include <Windows.h>

namespace Atena
{
	class ATENA_API Window
	{
	public:
		Window(const int & width, const int & height);

		bool isClosed() const;
		bool pollEvents();

		static Context * getContext() { return context; };
	private:
		static Context * context;
		MSG message;
	};
}