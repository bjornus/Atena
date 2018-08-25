#include "System/Window.hpp"

#include "Rendering/Mesh.hpp"
#include "Rendering/Shader.hpp"

using namespace Vawel;

int main()
{
	Window window(800, 600);

	std::vector<Vertex> vertices =
	{
		{ { -0.5f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { 0.5, 0.5, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.5, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
		{ { 0.5, -0.5f, 0.0f }, { 1.0f, 0.0f, 1.0f, 1.0f } }
	};

	std::vector<unsigned int> indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	Mesh mesh(vertices, indices);
	Shader shader("shader.shader");
	shader.bind();

	while (!window.isClosed())
	{
		if (window.pollEvents())
		{

		}
		else
		{
			window.getContext()->clear();

			mesh.draw();

			window.getContext()->present();
		}
	}

	return 0;
}