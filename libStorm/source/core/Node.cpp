#include "core/node.hpp"

using namespace Storm;

Node::Node()
{

}

void Node::add_child(Node* child)
{
	children.push_back(nodeptr_t(child));
}

nodeptr_t Node::get_child_by_name(std::string name)
{
	for (auto child : children)
	{
		if (child->name == name)
			return child;
	}
	return nullptr;
}

nodecontainer_t Node::get_children()
{
	return children;
}

void Node::draw()
{
	for (auto child : children)
		child->draw();
}