#pragma once

#include <map>

#include "core/Resource.hpp"
#include <glm/glm.hpp>
#include <freetype/freetype.h>

namespace Storm::Resources
{
	struct FontConfig
	{
		uint32_t height = 32;
		std::string filepath;
	};

	struct FontCharacter
	{
		uint32_t textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		uint32_t advanceOffset;
	};

	class Font : public Resource
	{
	private:
		FT_Face face;
		std::map<char, FontCharacter> characters;

	public:
		Font(FontConfig cfg);
		~Font();
	};
};