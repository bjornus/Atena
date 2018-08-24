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
		~Window();

		bool isClosed();
		bool pollEvents();

		Context * getContext();
	private:
		MSG message;
		Context * context;
	};
}