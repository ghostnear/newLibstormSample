#include "lib.hpp"

#include "graphics/all.hpp"
#include "networking/all.hpp"

#include <SDL2/SDL_opengl.h>

using namespace Storm;

void Storm::init()
{
	// Graphics is kinda required.
	Graphics::init_subsystem();

#ifndef STORM_DISABLE_NETWORKING
	Networking::init_subsystem();
#endif
}

void Storm::main_loop()
{
	static SDL_Event event;
	while (true)
	{
		auto& windowsList = Graphics::WindowManager::get_windows();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				// TODO: handle more events.

				// On quit.
			case SDL_QUIT:
				windowsList.clear();
				return;
				break;

				// On window events.
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
					// A window has been closed.
				case SDL_WINDOWEVENT_CLOSE:
					Graphics::WindowManager::remove_window_by_id(event.window.windowID);
					break;
				default: break;
				}
				break;

			default: break;
			}
		}

		for (auto window : windowsList)
		{
			window->set_current();

			window->clear();
			if(window->get_root_node() != nullptr)
				window->get_root_node()->draw();

			SDL_GL_SwapWindow(window->get_internal_handler());
		}
	}
}

int32_t Storm::quit()
{
	Graphics::end_subsystem();

#ifndef STORM_DISABLE_NETWORKING
	Networking::end_subsystem();
#endif

	return EXIT_SUCCESS;
}