#pragma once

#include <cstdint>

namespace Storm
{
	void init();
	void main_loop();
	void render_loop();
	void event_loop();
	int32_t quit();
};