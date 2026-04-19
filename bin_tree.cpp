#include "bin_tree.h"

BinTree::BinTree() {
	root = nullptr;
	_size = _height = 0;
}

//Destructor deletes root, which recursively deletes all nodes
BinTree::~BinTree() {
	delete root;
}

//Initializes the root node, or delegates to add() to insert a new leaf
void BinTree::add(const Student& s)
{
	Node* n = new Node(s);

	if (!root) {
		root = n;
		_size++;
	}
	else {
		_height = root->add(n, _size + 1);
		_size++;
	}
}

//Returns whether the given value exists in the binary tree
bool BinTree::contains(size_t i) const
{
	if (!root)
		return false;

	return root->contains(i);
}

//Returns the number of elements of the tree
size_t BinTree::size() const {
	return _size;
}

//If a root already exists, calls inOrder() on the root node to retrieve the tree elements in sorted order
std::vector<const Student*> BinTree::inOrder()
{
	std::vector<const Student*>elements;

	if (root)
		root->inOrder(elements);

	return elements;
}

//Returns the expected minimum height of the tree
size_t BinTree::height() const {
	return _height;
}
