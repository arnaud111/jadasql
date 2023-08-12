//
// Created by a833444 on 07/08/2023.
//

#ifndef JADA_LIST_H
#define JADA_LIST_H

#include "Node.h"

template <typename T>

class List {

    Node<T> *first = nullptr;

    public :
        int len() {
            int i = 0;

            Node<T> *tmp = first;

            while (tmp != nullptr) {
                i++;
                tmp = tmp->next;
            }

            return i;
        }

        void append(T val) {

            if (first == nullptr) {
                first = new Node<T>(val);
                return;
            }

            Node<T> *tmp = first;

            while (tmp->next != nullptr) {
                tmp = tmp->next;
            }

            tmp->setNext(val);
        }

        T get(int index) {

            Node<T> *tmp = first;
            if (tmp == nullptr) throw std::invalid_argument("Index out of bounds");

            for (int i = 0; i < index; i++) {
                tmp = tmp->next;
                if (tmp == nullptr) throw std::invalid_argument("Index out of bounds");
            }

            return tmp->val;
        }

        void remove(int index) {

            Node<T> *tmp = first;
            if (tmp == nullptr) throw std::invalid_argument("Index out of bounds");

            for (int i = 0; i < index - 1; i++) {
                tmp = tmp->next;
                if (tmp == nullptr) throw std::invalid_argument("Index out of bounds");
            }

            if (tmp->next == nullptr) throw std::invalid_argument("Index out of bounds");

            tmp->next = tmp->next->next;
        }
};

#endif //JADA_LIST_H
