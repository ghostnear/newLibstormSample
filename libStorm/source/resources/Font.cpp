#include "resources/Font.hpp"

using namespace Storm::Resources;

#include <mutex>

static FT_Library* ftl = nullptr;

Font::Font(FontConfig cfg)
{
	// Init freetype if it wasn't already.
	if (ftl == nullptr)
	{
		ftl = new FT_Library();
		if (FT_Init_FreeType(ftl))
			throw std::runtime_error("Could not init the FreeType library!");
	}

	if (FT_New_Face(*ftl, cfg.filepath.c_str(), 0, &face))
		throw std::runtime_error("Could not load font face at path: " + cfg.filepath);
}

Font::~Font()
{

}