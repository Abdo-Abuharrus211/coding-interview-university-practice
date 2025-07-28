//
// Created by dev on 27/07/25.
//

#include <cstdlib>

class Node {
    int data;
    Node *next;
    Node *prev;

public:
    // C++ makes you mark constructors that are callable with a single param to avoid implicitly assigning defaults
    explicit Node(int data, Node *next = nullptr, Node *prev = nullptr) {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }

    // TODO: some of these may become redundant as LinkedList will also need to implement some
    // Move the members to the public?

    int val() const {
        return this->data;
    }

    Node *getNext() const {
        return this->next;
    }

    Node *getPrev() const {
        return this->prev;
    }

    void setVal(int val) {
        this->data = val;
    }

    void setNext(Node *next) {
        this->next = next;
    }

    void setPrev(Node *prev) {
        this->prev = prev;
    }
};


class LinkedList {
    int size;
    Node *head;

public:
    explicit LinkedList(int val) {
        this->head = new Node(val);
        this->size = 1;
    }

    // TODO: replace with simple size getter later on when adding insert functions that increment size
    int getSize() const {
        Node *current = this->head;
        int size = 0;
        while (current != nullptr) {
            size++;
            current = current->getNext();
        }
        return size;
    }

    Node *getHead() const {
        return head;
    }

    bool empty() const {
        return size == 0;
    }

    int valueAt(int index) const {
        Node *current = this->head;
        int i = 0;
        // could use a for loop with current as the ptr...
        while (current != nullptr) {
            if (i == index) {
                return current->val();
            }
            i++;
            current = current->getNext();
        }
        return 0;
    }
};


int main() {
    LinkedList list = LinkedList(1);


    free(list);
    return 0;
}
