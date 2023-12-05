#ifndef JADA_UNIQUEINDEX_HPP
#define JADA_UNIQUEINDEX_HPP

#include "Node.hpp"

template<typename V, comparable K>
class UniqueIndex {
private:
public:
	Node<V, K>* root;

	explicit UniqueIndex(int max) {
		root = new LeafNode<V, K>(max);
	}

	V* operator[](K* key) {
		root->getValueAt(key);
	}

	void insert(K* key, V* value) {
		if (!root->canInsert(key)) {
			K* newKey = root->keys[(root->max + 1) / 2];
			auto newNode = root->split();
			auto newRoot = new Node<V, K>(root->max);
			newRoot->insertKey(0, newKey);
			newRoot->insertChild(0, root);
			newRoot->insertChild(1, newNode);
			newRoot->n = 1;
			root = newRoot;
		}
		root->insertAt(key, value);
	}
};

#endif //JADA_UNIQUEINDEX_HPP
