#pragma once

#include "../core/Node.hpp"

namespace Storm::Nodes
{
	struct TextNodeConfig
	{

	};

	class TextNode : public Node
	{
	public:
		TextNode(TextNodeConfig cfg);
		void draw();
	};
};