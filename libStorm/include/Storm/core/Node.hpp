#pragma once

#include <map>
#include <mutex>
#include <vector>

namespace Storm
{
	// The building block of a scene.
	class Node;

	typedef std::shared_ptr<Node> nodeptr_t;
	typedef std::vector<nodeptr_t> nodecontainer_t;

	class Node
	{
	protected:
		nodecontainer_t children;
		std::string name;

	public:
		Node();
		void add_child(Node* child);
		nodeptr_t get_child_by_name(std::string name);
		nodecontainer_t get_children();
		virtual void draw();
	};
};