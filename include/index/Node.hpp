#ifndef JADA_NODE_HPP
#define JADA_NODE_HPP

#include <utils/Comparable.hpp>
#include <type_traits>
#include <cstdio>
#include <cstdlib>
#include <utils/instanceof.hpp>

template<typename V, comparable K>
class LeafNode;

template<typename V, comparable K>
class Node {
public:
	explicit Node(int m) {
		max = m;
		keys = (K**)malloc(sizeof(K*) * m);
		children = (Node<V, K>**) malloc((sizeof(Node<V, K>*) * (m+1)));
	}

	K **keys;
	int n = 0;
	Node<V, K> **children;
	int max;

	virtual V *getValueAt(K *key) {
		for (int i = 0; i < n; ++i) {
			if (*key < *(keys[i])) {
				return children[i]->getValueAt(key);
			}
		}
		return children[n]->getValueAt(key);
	}

	virtual void insertAt(K *key, V *value) {
		for(int i = 0; i < n; ++i) {
			if(*key < *(keys[i])) {
				if(children[i]->canInsert(key)) {
					children[i]->insertAt(key, value);
					return;
				} else {
					insertKey(children[i]->keys[max / 2]);
					auto tmp = children[i]->split();
					insertChild(i+1, tmp);
					this->n++;
					if(*key < *(keys[i])){
						children[i]->insertAt(key, value);
					} else {
						children[i+1] ->insertAt(key, value);
					}
					return;
				}
			}
		}
		if(children[n]->canInsert(key)) {
			children[n]->insertAt(key, value);
		} else {
			insertKey(children[n]->keys[max / 2]);
			auto tmp = children[n]->split();
			insertChild(n+1, tmp);
			this->n++;
			if(*key < *(keys[n])){
				children[n]->insertAt(key, value);
			} else {
				children[n+1] ->insertAt(key, value);
			}
		}
		return;
	}

	virtual bool canInsert(K *key) {
		for(int i = 0; i < n; ++i) {
			if(*key < *(keys[i])) {
				if(children[i]->canInsert(key)) {
					return true;
				}
				return n < max;
			}
		}
	}

	virtual Node<V, K>* split() {
		auto *newNode = new Node<V, K>(max);
		for(int i = (max+1)/2; i < max; ++i){
			newNode->children[i - (max+1/2)] = children[i];
			newNode->keys[i - (max+1)/2] = keys[i];
			children[i] = nullptr;
			keys[i] = nullptr;
		}
		newNode->n = max / 2;
		this->n = max / 2;
		newNode->children[max - (max+1)/2] = children[max];
		children[max] = nullptr;
		return newNode;
	}

	void insertChild(int index, Node *child) {
		for(int i = n; i >= index; --i) {
			children[i + 1] = children[i];
		}
		children[index] = child;
	}

	void insertKey(int index, K *key) {
		for (int i = n - 1; i >= index; --i) {
			keys[i + 1] = keys[i];
		}
		keys[index] = key;
	}

	void insertKey(K *key) {
		for(int i = 0; i < n; ++i) {
			if(*key < *(keys[i])){
				insertKey(i, key);
				return;
			}
		}
		insertKey(n, key);
	}

protected:

};

template<typename V, comparable K>
class LeafNode : public Node<V, K> {
public:
	explicit LeafNode(int m) : Node<V, K>(m) {
		this->max = m;
		this->keys = (K**)malloc(sizeof(K*) * m);
		this->children = nullptr;
		this->records = (V**) malloc(sizeof(V*) * (m+1));
	};

	V **records = nullptr;

	LeafNode *next = nullptr;

	V *getValueAt(K *key) {
		for (int i = 0; i < this->n; ++i) {
			if(*(this->keys[i]) == *key) {
				return records[i];
			}
		}
		return (V *) nullptr;
	}

	void insertAt(K *key, V *value) {
		for(int i = 0; i < this->n; ++i) {
			if(*key < *(this->keys[i])) {
				this->insertKey(i, key);
				this->insertRecord(i, value);
				this->n++;
				return;
			}
		}
		this->insertKey(this->n, key);
		this->insertRecord(this->n, value);
		this->n++;
	}

	Node<V, K>* split() {
		auto *newNode = new LeafNode<V, K>(this->max);
		for(int i = (this->max+1)/2; i < this->max; ++i){
			newNode->records[i - (this->max+1)/2] = this->records[i];
			newNode->keys[i - (this->max+1)/2] = this->keys[i];
			this->records[i] = nullptr;
			this->keys[i] = nullptr;
		}
		newNode->n = this->max / 2;
		this->n = (this->max+1) / 2;
		newNode->records[this->max - (this->max+1)/2] = this->records[this->max];
		this->records[this->max] = nullptr;
		return newNode;
	}

private:

	bool canInsert(K *key) {
		return this->n < this->max;
	}

	void insertRecord(int index, V *value) {
		for(int i = this->n; i >= index; --i) {
			records[i + 1] = records[i];
		}
		records[index] = value;
	}
};

#endif //JADA_NODE_HPP
