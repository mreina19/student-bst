#ifndef node_h
#define node_h

#include <vector>
#include <string>

struct Student {
	size_t number;
	std::string name;
};

class Node
{
	Node* right, * left;
	Student s;

	public:
		Node(const Student& s);
		~Node();
		size_t add(Node* n, size_t count);
		bool contains(size_t i) const;
		void inOrder(std::vector<const Student*>& elements);
};
#endif