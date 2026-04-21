#include "bin_tree.h"
#include <cmath>
#include <stdexcept>

BinTree::BinTree() {
	root = nullptr;
	_size = _height = 0;
}

//Destructor deletes root, which recursively deletes all nodes
BinTree::~BinTree() {
	delete root;
}

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

//Initializes the root node, or delegates to add() to insert a new leaf
void BinTree::add(const Student& s)
{
	if (s.name.empty())
        throw std::invalid_argument("Name cannot be empty.");

    if (!nameCheck(s.name))
        throw std::invalid_argument("Invalid name format.\nName cannot have leading or trailing spaces, and must contain only letters and spaces.");

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

//Removes the student with the given number from the tree.
//Returns true if found and deleted, false if the element didn't exist.
bool BinTree::remove(size_t number)
{
    if (!root)
        return false;

    bool found = false;
    root = root->remove(number, found);

    //Only update size and height if a deletion actually occurred
    if (found) {
        _size--;
        _height = (_size > 0) ? (size_t)log2((double)_size) : 0;
    }

    return found;
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
