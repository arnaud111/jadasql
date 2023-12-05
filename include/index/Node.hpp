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
		keys = (K **) malloc(sizeof(K *) * m);
		children = (Node<V, K> **) malloc((sizeof(Node<V, K> *) * (m + 1)));
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
		for (int i = 0; i < n; ++i) {
			if (*key < *(keys[i])) {
				if (children[i]->canInsert(key)) {
					children[i]->insertAt(key, value);
					return;
				} else {
					insertKey(children[i]->keys[max / 2]);
					auto tmp = children[i]->split();
					insertChild(i + 1, tmp);
					this->n++;
					if (*key < *(keys[i])) {
						children[i]->insertAt(key, value);
					} else {
						children[i + 1]->insertAt(key, value);
					}
					return;
				}
			}
		}
		if (children[n]->canInsert(key)) {
			children[n]->insertAt(key, value);
		} else {
			insertKey(children[n]->keys[max / 2]);
			auto tmp = children[n]->split();
			insertChild(n + 1, tmp);
			this->n++;
			children[n]->insertAt(key, value);
		}
	}

	virtual bool canInsert(K *key) {
		for (int i = 0; i < n; ++i) {
			if (*key < *(keys[i])) {
				if (children[i]->canInsert(key)) {
					return true;
				}
				return n < max;
			}
		}
		return n < max;
	}

	virtual Node<V, K> *split() {
		auto *newNode = new Node<V, K>(max);
		for (int i = 0; i < (max - 1) / 2; ++i) {
			newNode->children[i] = children[(max / 2 + 1) + i];
			newNode->keys[i] = keys[(max / 2 + 1) + i];
			children[(max / 2 + 1) + i] = nullptr;
			keys[(max / 2 + 1) + i] = nullptr;
		}
		this->n = max / 2;
		newNode->n = (max - 1) / 2;
		newNode->children[(max - 1 ) / 2] = children[max];
		children[max] = nullptr;
		return newNode;
	}

	void insertChild(int index, Node *child) {
		for (int i = n; i >= index; --i) {
			children[i + 1] = children[i];
		}
		if(instanceof<LeafNode<V, K>>(children[0])){
			if(index != 0){
				((LeafNode<V, K>*)children[index-1])->next = (LeafNode<V, K>*)child;
			}
			if(index <= n) {
				((LeafNode<V,K>*)child)->next = (LeafNode<V, K>*)children[index+1];
			}
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
		for (int i = 0; i < n; ++i) {
			if (*key < *(keys[i])) {
				insertKey(i, key);
				return;
			}
		}
		insertKey(n, key);
	}

	virtual LeafNode<V, K>* firstLeaf() {
		return children[0]->firstLeaf();
	}

	virtual void remove(K *key) {
		for(int i = 0; i < this->n; ++i) {
			if(*key < *this->keys[i]) {
				this->children[i]->remove(key);
				if(this->children[i]->n < this->max / 2) {
					if(equilibrate(this->children[i], this->children[i+1], false)) {
						this->keys[i] = this->children[i+1]->keys[0];
					} else {
						delete this->removeChild(i);
						delete this->removeKey(i);
						this->n--;
					}
				}
				return;
			}
		}
		this->children[max]->remove(key);
		if(this->children[max]->n < this->max / 2) {
			if(equilibrate(this->children[max], this->children[max - 1], true)) {
				this->keys[max - 1] = this->children[max]->keys[0];
			} else {
				delete this->removeKey(max - 1);
				delete this->removeChild(max);
				this->n--;
			}
		}

	}

	K *removeKey(int index) {
		K *tmp = this->keys[index];
		this->keys[index] = nullptr;
		for(int i = index; i < this->n - 1; ++i) {
			this->keys[i] = this->keys[i + 1];
		}
		return tmp;
	}

	Node<K, V> *removeChild(int index) {
		Node<K, V> *tmp = this->children[index];
		this->children[index] = nullptr;
		for(int i = 0; i < this->n; ++i) {
			this->children[i] = this->children[i + 1];
		}
		return tmp;
	}

	bool equilibrate(Node<K, V> *current, Node<K, V> *equilibrateNode, bool prev) {
		if(instanceof<LeafNode<K, V>>(current)) {
			return equilibrateLeaf((LeafNode<K, V> *)current, (LeafNode<K, V> *)equilibrateNode, prev);
		}else {
			return equilibrateInternalNode(current, equilibrateNode, prev);
		}
	}

	bool equilibrateInternalNode(Node<K, V> *current, Node<K, V> *equilibrateNode, bool prev) {
		if(equilibrateNode->n > max / 2) {
			auto tmp = equilibrateNode->removeChild(prev ? equilibrateNode->n : 0);
			current->insertChild(prev ? 0 : current->n , tmp);
			equilibrateNode->n--;
			current->n++;
			return true;
		} else {
			for(int i = 0; i < current->n + 1; ++i) {
				equilibrateNode->insertChild(equilibrateNode->n + 1 + i, current->children[i]);
			}
			equilibrateNode->n += current->n;
			return false;
		}
	}

	bool equilibrateLeaf(LeafNode<K, V> *current, LeafNode<K, V> *equilibrateNode, bool prev) {
		if(equilibrateNode->n > max / 2) {
			auto tmp = equilibrateNode->removeRecord(prev ? equilibrateNode->n : 0);
			current->insertRecord(prev ? 0 : current->n, tmp);
			equilibrateNode->n--;
			current->n++;
			return true;
		} else {
			for(int i = 0; i < current->n; ++i) {
				equilibrateNode->insertRecord(equilibrateNode->n + 1 + i, current->records[i]);
			}
			equilibrateNode->n += current->n;
			return false;
		}
	}

protected:

};

template<typename V, comparable K>
class LeafNode : public Node<V, K> {
public:
	explicit LeafNode(int m) : Node<V, K>(m) {
		this->max = m;
		free(this->children);
		this->children = nullptr;
		this->records = (V **) malloc(sizeof(V *) * (m + 1));
	};

	V **records;

	LeafNode *next = nullptr;

	V *getValueAt(K *key) {
		for (int i = 0; i < this->n; ++i) {
			if (*(this->keys[i]) == *key) {
				return records[i];
			}
		}
		return (V *) nullptr;
	}

	void insertAt(K *key, V *value) {
		for (int i = 0; i < this->n; ++i) {
			if (*key < *(this->keys[i])) {
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

	Node<V, K> *split() {
		auto *newNode = new LeafNode<V, K>(this->max);
		for (int i = 0; i <= this->max / 2; ++i) {
			newNode->records[i] = this->records[this->max / 2 + i];
			newNode->keys[i] = this->keys[this->max / 2 + i];
			this->records[this->max / 2 + i] = nullptr;
			this->keys[this->max / 2 + i] = nullptr;
		}
		newNode->n = (this->max + 1) / 2;
		this->n = this->max / 2;
		return newNode;
	}

	LeafNode<V, K>* firstLeaf() {
		return this;
	}

	void remove(K *key) {
		for(int i = 0; i < this->n; ++i) {
			if(*key == *this->keys[i]) {
				delete this->removeKey(i);
				delete removeRecord(i);
				this->n--;
				return;
			}
		}
	}

	V* removeRecord(int index) {
		V *tmp = this->records[index];
		this->records[index] = nullptr;
		for(int i = index; i < this->n - 1; ++i) {
			this->records[i] = this->records[i + 1];
		}
		return tmp;
	}

	bool canInsert(K *key) {
		return this->n < this->max;
	}

	void insertRecord(int index, V *value) {
		for (int i = this->n; i >= index; --i) {
			records[i + 1] = records[i];
		}
		records[index] = value;
	}
};

#endif //JADA_NODE_HPP
