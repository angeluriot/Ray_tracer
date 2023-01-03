#include <GL/glew.h>
#include <SDL.h>

#include "Raytracer.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Introduction to Computer Graphics - Raytracer" << std::endl << std::endl;

	char* default_input = "scenes/scene01-phong.yaml";
	char* input_file;

	if ((argc < 2 || argc > 3) && default_input == "")
	{
		std::cerr << "Usage: " << argv[0] << " in-file" << std::endl;
		return EXIT_FAILURE;
	}

	input_file = argc < 2 ? default_input : argv[1];

	if (!Raytracer::read_scene(input_file))
	{
		std::cerr << "Error: reading scene from " << input_file << " failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window* window = SDL_CreateWindow("Ray tracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

	if (window == nullptr)
	{
		SDL_Log("Could not create a window: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);

	if (context == nullptr)
	{
		SDL_Log("Could not create a GL context: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if (glewError != GLEW_OK)
	{
		SDL_Log("Error initializing GLEW! %s", glewGetErrorString(glewError));
		return EXIT_FAILURE;
	}

	bool quit = false;

	while (!quit)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				}
				break;
			}
		}

		//Raytracer::render();
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
