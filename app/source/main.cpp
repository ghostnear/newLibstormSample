#define STORM_DISABLE_NETWORKING

#include <Storm/all.hpp>

using namespace Storm;

int main(int argc, char* argv[])
{
	try {
		Storm::init();

		auto window = Graphics::WindowManager::add_window(Graphics::WindowConfig{
			.width = 960,
			.height = 540,
			.name = "LibStorm OpenGL test",
			.clearColor = { .r = 125, .g = 125, .b = 125, .a = 255 }
		});
		window->set_root_node(new Nodes::TextNode(Nodes::TextNodeConfig{

		}));

		// TODO: maybe my big brain is too big, let's fix that.
		// So we got 1 main thread, 1 update *main* thread, and myb a thread pool for other stuff like loading.

		// Premade main loop for ease of use.
		Storm::main_loop();
	}
	catch (const std::runtime_error& error)
	{
		Graphics::show_error_window(error.what());
		Storm::quit();
		return EXIT_FAILURE;
	}

	return Storm::quit();
}
