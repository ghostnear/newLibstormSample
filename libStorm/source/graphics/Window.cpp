#include "graphics/window.hpp"

#include <stdexcept>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

using namespace Storm;
using namespace Storm::Graphics;

//
//	Window
//

Window::Window(WindowConfig cfg)
{
	// Create window.
	clearColor = cfg.clearColor;
	window = SDL_CreateWindow(
		cfg.name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		cfg.width, cfg.height, SDL_WINDOW_OPENGL
	);
	if (window == NULL)
		throw std::runtime_error("Could not create SDL window: " + std::string(SDL_GetError()));

	// Create OpenGL context.
	glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL)
		throw std::runtime_error("Could not initialize OpenGL context: " + std::string(SDL_GetError()));

	// Initialize GLEW.
	glewExperimental = GL_TRUE;
	static GLenum error;
	if ((error = glewInit()) != GLEW_OK)
		throw std::runtime_error("Could not set up GLEW: " + std::string((char*)glewGetErrorString(error)));
}

Window::~Window()
{
	closed = false;
	if (window != NULL)
		SDL_DestroyWindow(window);
}

void Window::clear()
{
	glClearColor(clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::set_root_node(Node* newRoot)
{
	root = nodeptr_t(newRoot);
}

nodeptr_t Window::get_root_node()
{
	return root;
}

SDL_Window* Window::get_internal_handler()
{
	return window;
}

void Graphics::Window::set_current()
{
	SDL_GL_MakeCurrent(window, glContext);
}

//
//	WindowManager
//

WindowManager* WindowManager::instance = nullptr;

WindowManager* WindowManager::get_instance()
{
	if (instance == nullptr)
		instance = new WindowManager();
	return instance;
}

void WindowManager::remove_window_by_id(uint32_t id)
{
	auto& windowsList = get_instance()->get_windows();
	auto new_end = std::remove_if(windowsList.begin(), windowsList.end(),
		[id](windowptr_t window) {
			return SDL_GetWindowID(window->get_internal_handler()) == id;
		}
	);
	windowsList.erase(new_end, windowsList.end());
}

Window* WindowManager::add_window(WindowConfig cfg)
{
	windowptr_t newWindow = windowptr_t(new Window(cfg));
	get_instance()->windows.push_back(newWindow);
	return newWindow.get();
}

windowlist_t& WindowManager::get_windows()
{
	return get_instance()->windows;
}

WindowManager::WindowManager()
{
	// Do nothing.
}

WindowManager::~WindowManager()
{
	while (windows.size() != 0)
		windows.pop_back();
}

//
//	Other functions.
//

void Graphics::show_error_window(std::string message, SDL_Window* window)
{
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,
		"Error!",
		message.c_str(), window
	);
}