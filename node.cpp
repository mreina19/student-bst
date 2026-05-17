#include "node.h"
#include <cmath>
#include <stdexcept>

using namespace std;

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

//Removes the node with the given number from the subtree.
//Sets found to true if the element was located and deleted. Returns the updated subtree root.
Node* Node::remove(size_t number, bool& found)
{
    if (number < s.number)
    {
        //Target is smaller, traverse left
        if (left)
            left = left->remove(number, found);
    }
    else if (number > s.number)
    {
        //Target is larger, traverse right
        if (right)
            right = right->remove(number, found);
    }
    else
    {
        //Node found
        found = true;

        //Leaf node. No children, simply delete
        if (!left && !right) {
            delete this;
            return nullptr;
        }

        //Only right child. Promote it
        if (!left) {
            Node* successor = right;
            right = nullptr;    //Detach before deleting to prevent cascading destruction
            delete this;
            return successor;
        }

        //Only left child. Promote it
        if (!right) {
            Node* successor = left;
            left = nullptr;
            delete this;
            return successor;
        }

        //Two children. Replace with in-order successor (leftmost node of right subtree)
        Node* minNode = right;
        while (minNode->left)
            minNode = minNode->left;

        //Copy successor's data into this node, then remove the successor
        s = minNode->s;
        right = right->remove(minNode->s.number, found);
    }

    return this;
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