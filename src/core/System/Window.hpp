#pragma once

#include "../Rendering/Context.hpp"

#include <Windows.h>

namespace Atena
{
	class Window
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