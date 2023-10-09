#include <index/UniqueIndex.hpp>
#include <cstdlib>
#include <cstdio>

class MyInt: Comparable<MyInt> {
public:

	explicit MyInt(int v) {
		value = v;
	}

	int value;

	bool operator< (MyInt const& other) const override {
		return value < other.value;
	}

	bool operator<= (MyInt const& other) const override {
		return value <= other.value;
	}

	bool operator> (MyInt const& other) const override {
		return value > other.value;
	}

	bool operator>= (MyInt const& other) const override {
		return value >= other.value;
	}

	bool operator== (MyInt const& other) const override {
		return value == other.value;
	}

	bool operator!= (MyInt const& other) const override {
		return value != other.value;
	}
};

int mainOld() {

	auto *test = new Node<MyInt, MyInt>(5);
	test->keys = (MyInt**) malloc(sizeof(MyInt*) * 2);
	test->keys[0] = new MyInt(10);
	test->keys[1] = new MyInt(20);
	test->children = (Node<MyInt, MyInt>**)malloc(sizeof(Node<MyInt, MyInt>*) * 2);
	test->n = 2;
	test->children[0] = new LeafNode<MyInt, MyInt>(5);
	test->children[1] = new LeafNode<MyInt, MyInt>(5);
	test->children[0]->n = 2;
	test->children[0]->keys = (MyInt**) malloc(sizeof(MyInt*) * 2);
	test->children[0]->keys[0] = new MyInt(2);
	test->children[0]->keys[1] = new MyInt(6);
	test->children[1]->n = 0;
	test->children[1]->keys = (MyInt**) malloc(sizeof(MyInt*) * 0);
	((LeafNode<MyInt, MyInt>*)test->children[0])->records[0] = new MyInt(2);
	((LeafNode<MyInt, MyInt>*)test->children[0])->records[1] = new MyInt(6);

	printf("test->n = %d\n", test->n);
	for(int i = 0; i < test->n; ++i) {
		printf("test->children[%d]->n = %d\n", i, test->children[i]->n);
		for(int j = 0; j < test->children[i]->n; ++j) {
			printf("test->children[%d]->records[%d] = %d\n", i, j,  ((LeafNode<MyInt, MyInt>*)test->children[i])->records[j]->value);
		}
		printf("test->keys[%d] = %d\n", i, test->keys[i]->value);
	}

	test->insertAt(new MyInt(4), new MyInt(4));
	test->insertAt(new MyInt(5), new MyInt(5));
	test->insertAt(new MyInt(3), new MyInt(3));

	printf("\ntest->n = %d\n", test->n);
	for(int i = 0; i < test->n; ++i) {
		printf("test->children[%d]->n = %d\n", i, test->children[i]->n);
		for(int j = 0; j < test->children[i]->n; ++j) {
			printf("test->children[%d]->records[%d] = %d\n", i, j,  ((LeafNode<MyInt, MyInt>*)test->children[i])->records[j]->value);
		}
		printf("test->keys[%d] = %d\n", i, test->keys[i]->value);
	}

	test->insertAt(new MyInt(8), new MyInt(8));
	printf("\ntest->n = %d\n", test->n);
	for(int i = 0; i < test->n; ++i) {
		printf("test->children[%d]->n = %d\n", i, test->children[i]->n);
		for(int j = 0; j < test->children[i]->n; ++j) {
			printf("test->children[%d]->records[%d] = %d\n", i, j,  ((LeafNode<MyInt, MyInt>*)test->children[i])->records[j]->value);
		}
		printf("test->keys[%d] = %d\n", i, test->keys[i]->value);
	}

	return 1;
}

int main() {
	auto test = UniqueIndex<MyInt, MyInt>(5);
	test.insert(new MyInt(0), new MyInt(0));
	test.insert(new MyInt(1), new MyInt(1));
	test.insert(new MyInt(2), new MyInt(2));
	test.insert(new MyInt(3), new MyInt(3));
	test.insert(new MyInt(4), new MyInt(4));
	test.insert(new MyInt(5), new MyInt(5));
	test.insert(new MyInt(6), new MyInt(6));
	test.insert(new MyInt(7), new MyInt(7));
	test.insert(new MyInt(8), new MyInt(8));
	test.insert(new MyInt(9), new MyInt(9));
	test.insert(new MyInt(10), new MyInt(10));
	test.insert(new MyInt(11), new MyInt(11));
	test.insert(new MyInt(12), new MyInt(12));
	test.insert(new MyInt(13), new MyInt(13));
	test.insert(new MyInt(14), new MyInt(14));
	test.insert(new MyInt(15), new MyInt(15));
	test.insert(new MyInt(16), new MyInt(16));
	test.insert(new MyInt(17), new MyInt(17));
	test.insert(new MyInt(18), new MyInt(18));
	test.insert(new MyInt(19), new MyInt(19));
	test.insert(new MyInt(20), new MyInt(20));

	auto f = test.root->firstLeaf();

	int j = 0;
	while(f != nullptr) {
		for(int i = 0; i < f->n; ++i) {
			printf("test[%d] = %d\n", j++, f->records[i]->value);
		}
		printf("\n");
		f = f->next;
	}
	test.insert(new MyInt(21), new MyInt(21));
	test.insert(new MyInt(22), new MyInt(22));
	test.insert(new MyInt(23), new MyInt(23));

	f = test.root->firstLeaf();

	j = 0;
	while(f != nullptr) {
		for(int i = 0; i < f->n; ++i) {
			printf("test[%d] = %d\n", j++, f->records[i]->value);
		}
		printf("\n");
		f = f->next;
	}

//	for(int i = 0; i < test.root->n + 1; ++i) {
//		for(int j = 0; j < test.root->children[i]->n; ++j) {
//			printf("test->children[%d]->records[%d] = %d\n", i, j,  ((LeafNode<MyInt, MyInt>*)test.root->children[i])->records[j]->value);
//		}
//		if(i < test.root->n) {
//			printf("test->keys[%d] = %d\n", i, test.root->keys[i]->value);
//		}
//	}
	return 0;
}