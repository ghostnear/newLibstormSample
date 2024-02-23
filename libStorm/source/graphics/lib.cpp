#include "graphics/deps.hpp"

#include <stdexcept>
#include <SDL2/SDL.h>

using namespace Storm;

void Graphics::init_subsystem()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("Could not initialize SDL: " + std::string(SDL_GetError()));

	// Init OpenGL stuff.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void Graphics::end_subsystem()
{
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}