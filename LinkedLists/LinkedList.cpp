//
// Created by dev on 27/07/25.
//

#include <cstdlib>
#include <stdexcept>

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

    int getSize() const {
        return this->size;
    }

    Node *getHead() const {
        return head;
    }

    bool empty() const {
        return size == 0 || this->head == nullptr;
    }

    int valueAt(int index) const {
        if (index < 0 || index >= this->getSize()) {
            throw std::out_of_range("index out of range");
        }
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
        throw std::out_of_range("Current head is null!");
    }

    Node *find(int value) const {
        for (Node *j = this->head; j != nullptr; j = j->getNext()) {
            if (j->val() == value) {
                return j;
            }
        }
        return nullptr;
    }

    void pushFront(int index) {
        Node *newNode = new Node(index, nullptr, nullptr);
        newNode->setNext(this->head);
        if (this->head) {
            this->head->setPrev(newNode);
        }
        this->head = newNode;
        // redundant
        // this->head->setPrev(nullptr);
        this->size++;
    }

    bool insert(int value, int index) {
        if (index < 0 || this->size < index) {
            return false;
        }
        if (this->size == 0) {
            pushFront(value);
        }

        // walk to before the index node
        Node *current = this->head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->getNext();
        }
        Node *newNode = new Node(value, nullptr, nullptr);
        newNode->setNext(current->getNext());
        newNode->setPrev(current);
        current->setNext(newNode);

        // if next node exists, set its prev to new node
        if (newNode->getNext() != nullptr) {
            newNode->getNext()->setPrev(newNode);
        }
        this->size++;
        return true;
    }

    int popFront() {
        if (this->head == nullptr) {
            throw std::out_of_range("Linked List is empty!");
        }
        if (this->head) {
            int value = this->head->val();
            Node *oldHead = this->head;
            this->head = this->head->getNext();
            // if new head exists
            if (this->head) {
                this->head->setPrev(nullptr);
            }
            delete oldHead;
            this->size--;
            return value;
        }
        throw std::out_of_range("List's head is nullptr");
    }

    void pushBack(int value) {
        if (!this->head) {
            pushFront(value);
        }
        for (Node *current = this->head; current != nullptr; current = current->getNext()) {
            if (current->getNext() == nullptr) {
                Node *newNode = new Node(value, nullptr, nullptr);
                newNode->setNext(nullptr);
                current->setNext(newNode);
                newNode->setPrev(current);
                this->size++;
            }
        }
    }

    int popBack() {
        if (this->head == nullptr) {
            throw std::out_of_range("Linked List is empty!");
        }
        if (this->head->getNext() == nullptr) {
            int value = this->head->val();
            delete this->head; // delete the single node...
            this->head = nullptr;
            this->size--;
            return value;
        }
        for (Node *current = this->head->getNext(); current != nullptr; current = current->getNext()) {
            if (current->getNext() == nullptr) {
                int value = current->val();
                Node *tmp = current->getPrev();
                tmp->setNext(nullptr);
                delete current;
                this->size--;
                return value;
            }
        }
        throw std::out_of_range("List's head is nullptr");
    }

    void deleteAt(int index) {
        if (index < 0) {
            throw std::out_of_range("Index must not be negative!");
        }

        if (index == 0) {
            popFront();
            return;
        }
        // walk to
        Node *current = this->head;
        for (int i = 0; i < index; ++i) {
            if (!current) throw std::out_of_range("Index out of bounds");
            current = current->getNext();
        }
        if (!current) throw std::out_of_range("Index out of bounds");

        Node *prevNode = current->getPrev();
        Node *nextNode = current->getNext();

        if (prevNode) prevNode->setNext(nextNode);
        if (nextNode) nextNode->setPrev(prevNode);

        delete current;
        this->size--;
    }

    int getFront() const {
        if (this->head == nullptr) {
            throw std::out_of_range("Linked List is empty!");
        }
        return this->head->val();
    }

    int getBack() const {
        if (!this->head) {
            throw std::out_of_range("List's head is nullptr");
        }
        Node *current = this->head;
        while (current != nullptr) {
            if (current->getNext() == nullptr) {
                return current->val();
            }
            current = current->getNext();
        }
    }

    int valueNFromEnd(int n) const {
        if (this->size < n) {
            throw std::out_of_range("'n' is out of bounds!");
        }

        if (!this->head) {
            throw std::out_of_range("List's head is nullptr");
        }

        Node *current = this->head;
        int index = 0;
        while (current != nullptr) {
            if (this->size - index - 1 == n) {
                return current->val();
            }
            index++;
            current = current->getNext();
        }
    }

    void removeValue(int value) {
        if (this->head == nullptr) {
            throw std::out_of_range("Linked List is empty!");
        }

        Node *current = this->head;
        int index = 0;
        while (current != nullptr) {
            if (current->val() == value) {
                deleteAt(index);
                index--;
            }
            index++;
            current = current->getNext();
        }
    }

    // Since no parameters, going to do this iteratively instead of recursively
    Node *reverse() {
        if (this->head == nullptr) {
            throw std::out_of_range("Linked List is empty!");
        }

        if (this->head->getNext() == nullptr) {
            return this->head;
        }
        Node *current = this->head;
        Node *prev = nullptr;
        Node *next = nullptr;
        while (current != nullptr) {
            next = current->getNext();
            current->setNext(prev);
            current->setPrev(next);

            prev = current;
            current = next;
        }
        this->head = prev;
        return this->head;
    }
};


int main() {
    //Cannot convert LinkedList to parameter type void *
    LinkedList list = LinkedList(1);
    return 0;
}
