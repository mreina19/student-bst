#ifndef bin_tree_h
#define bin_tree_h

#include "node.h"

class BinTree
{
	Node* root;
	size_t _size, _height;

public:
	BinTree();
	~BinTree();
	void add(const Student& s);
	bool contains(size_t i) const;
	size_t size() const;
	std::vector<const Student*> inOrder();
	size_t height() const;
};
#endif