#include "node.h"
#include <cmath>
#include <stdexcept>

using namespace std;

//Validates that a name contains only alphabetic letters and spaces
static bool nameCheck(const std::string& name)
{
	if (name.empty())
		return false;

	//No leading or trailing spaces
	if (name.front() == ' ' || name.back() == ' ')
		return false;

	for (char c : name)
	{
		//isalpha() returns true if c is A-Z or a-z
		if (!isalpha(c) && c != ' ')
			return false;
	}

	return true;
}

Node::Node(const Student& s) {
	this->s = s;
	right = left = nullptr;
}

Node::~Node() {
	delete left;
	delete right;
}

//Recursively inserts a node into the correct BST position.
size_t Node::add(Node* n, size_t count)
{
	if (n->s.name.empty())
		throw invalid_argument("Name cannot be empty.");

	if (!nameCheck(n->s.name))
		throw invalid_argument("Invalid name format.\nName cannot have leading or trailing spaces, and must contain only letters and spaces.");

	//If the value to be inserted is less than the current node's value, traverse left
	if (n->s.number < s.number)
	{
		if (!left) {
			left = n;
			count++;
		}
		else
			count = left->add(n, count);
	}
	else if (n->s.number > s.number)
	{
		if (!right) {
			right = n;
			count++;
		}
		else
			count = right->add(n, count);
	}
	else
		throw invalid_argument("That element already exists in the tree.");

	//Minimum height = log2(count)
	return (size_t)log2((double)count);
}

//Traverses the tree to search for the target value
bool Node::contains(size_t i) const
{
	if (i < s.number)
	{
		if (left)
			return left->contains(i);
	}
	else if (i > s.number)
	{
		if (right)
			return right->contains(i);
	}
	else
		return true;

	return false;
}

//Inserts all tree elements into a vector in sorted order
void Node::inOrder(vector<const Student*>& elements)
{
	if (left)
		left->inOrder(elements);

	elements.push_back(&s);

	if (right)
		right->inOrder(elements);
}