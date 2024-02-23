#pragma once

#include <mutex>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "../core/Node.hpp"

namespace Storm::Graphics
{
	struct WindowConfig
	{
		int32_t width = 960;
		int32_t height = 540;
		std::string name = "<error>";
		SDL_Color clearColor = { 0 };
	};

	class Window
	{
	private:
		SDL_GLContext glContext = nullptr;
		SDL_Window* window = nullptr;
		nodeptr_t root = nullptr;
		SDL_Color clearColor = { 0 };

	public:
		Window(WindowConfig cfg);
		~Window();
		
		void clear();
		void poll_events();
		void set_current();
		void set_root_node(Node* newRoot);
		nodeptr_t get_root_node();
		SDL_Window* get_internal_handler();

		bool closed = false;
	};

	typedef std::shared_ptr<Window> windowptr_t;
	typedef std::vector<windowptr_t> windowlist_t;

	class WindowManager
	{
	private:
		windowlist_t windows;
		static WindowManager* instance;

		WindowManager();
		~WindowManager();

		static WindowManager* get_instance();

	public:
		// Singleton stuff.
		WindowManager(WindowManager& other) = delete;
		void operator=(const WindowManager&) = delete;
		static Window* add_window(WindowConfig cfg);
		static void remove_window_by_id(uint32_t id);
		static windowlist_t& get_windows();
	};

	void show_error_window(std::string message, SDL_Window* window = nullptr);
};