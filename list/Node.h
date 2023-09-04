//
// Created by arnaud on 07/08/2023.
//

#ifndef JADA_NODE_H
#define JADA_NODE_H

template <typename T>

class Node {

    public:
        T val;
        Node *next = nullptr;

    explicit Node(T v): val(v) {}

    void setNext(T value_next) {
        next = new Node<T>(value_next);
    }

};

#endif //JADA_NODE_H
