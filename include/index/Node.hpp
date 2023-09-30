#ifndef JADA_NODE_HPP
#define JADA_NODE_HPP

#include <utils/Comparable.hpp>
#include <type_traits>
#include <cstdio>

/*template <typename T>
concept ComparableContraint = requires(T a) {
	{ std::is_base_of<Comparable<T>, T>::value };
};*/

template<typename V, typename K>
class Node {
public:
	Comparable<K> **keys = nullptr;
	int n = 0;
	Node<V, K> **children = nullptr;

	virtual V *getValueAt(K *key) {
		for (int i = 0; i < n; ++i) {
			if (*key <= *(keys[i])) {
				return children[i]->getValueAt(key);
			}
		}
		return children[n]->getValueAt(key);
	}
};

template<typename V, typename K>
class LeafNode : public Node<V, K> {
public:
	V **records = nullptr;

	V *getValueAt(K *key) {
		for (int i = 0; i < this->n; ++i) {
			printf("%p\n", this->keys);
			if(*(this->keys[i]) == *key) {
				return records[i];
			}
		}
		return (V *) nullptr;
	}
};

#endif //JADA_NODE_HPP
