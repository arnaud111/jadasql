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

template <typename T>
class Test {
public:
	virtual bool operator==(T const& other) const = 0;
};

class MyInt2: Test<MyInt2> {
private:
	int value;

public:
	MyInt2(int v) {
		value = v;
	}

	bool operator==(MyInt2 const& other) const override{
		return value == other.value;
	}
};

int main() {
	MyInt2 **t = (MyInt2**)malloc(sizeof(MyInt2*) * 2);
	t[0] = new MyInt2(2);
	t[1] = new MyInt2(3);
	bool a = t[0] == t[1];
	printf("%d\n", a);

	auto *test = new Node<MyInt, MyInt>();
	MyInt(5) == MyInt(7);
	test->keys = (MyInt**) malloc(sizeof(MyInt*) * 2);
	test->keys[0] = new MyInt(8);
	test->keys[1] = new MyInt(12);
	test->children = (Node<MyInt, MyInt>**)malloc(sizeof(Node<MyInt, MyInt>*) * 3);
	test->n = 2;
	test->children[0] = new LeafNode<MyInt, MyInt>();
	test->children[1] = new LeafNode<MyInt, MyInt>();
	test->children[2] = new LeafNode<MyInt, MyInt>();
	test->children[0]->n = 2;
	test->children[0]->keys = (MyInt**) malloc(sizeof(MyInt*) * 2);
	test->children[0]->keys[0] = new MyInt(2);
	test->children[0]->keys[1] = new MyInt(6);
	((LeafNode<MyInt, MyInt>*)test->children[0])->records = (MyInt**)malloc(sizeof(MyInt*) * 2);
	((LeafNode<MyInt, MyInt>*)test->children[0])->records[0] = new MyInt(2);
	((LeafNode<MyInt, MyInt>*)test->children[0])->records[1] = new MyInt(6);
	auto tmp1 = MyInt(2);
	auto *tmp = test->getValueAt(&tmp1);
	printf("MyInt = %d", tmp->value);

	return 1;
}