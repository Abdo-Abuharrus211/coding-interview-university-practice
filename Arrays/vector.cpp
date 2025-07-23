//
// Created by dev on 22/07/25.
//


/*
    TODO: Implement Missing Destructor, Copy Constructor, Assignment Operator to avoid memory leaks
    when Vectors are copied or destroyed.
*/

#include <stdexcept>

class Vector {
    int capacity;
    int size;
    int *arr;

    /**
     * Instantiate a new array double the size, copy elements over, and delete previous.
     */
    void resize() {
        if (size == capacity) {
            capacity *= 2;
            int *newArr = new int[capacity];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
    };

public:
    /**
     *
     * @param initSize integer parameter representing the vector's size
     */
    Vector(const int initSize = 8) {
        capacity = initSize;
        size = 0;
        // Allocate the data in memory manually
        arr = new int[initSize];
    }

    // Destructor needed to nullify after deletion
    ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

    // Copy Constructor
    Vector(const Vector &other) : capacity(other.capacity), size(other.size) {
        arr = new int[capacity];
        for (int i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
    }

    // Copy Assignment Operator
    Vector &operator=(const Vector &other) {
        if (this != &other) {
            // Handle self-assignment
            delete[] arr; // Deallocate current memory
            capacity = other.capacity;
            size = other.size;
            arr = new int[capacity];
            for (int i = 0; i < size; ++i) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    // const because they don't mutate the class instance, apparently it's a C++ thing.
    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    /**
     *  Retrieve the element at a given index.
     *
     * @param index of the element to retrieve
     *
     * @return the integer value of the element
     */
    int at(const int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("index out of range");
        }

        // compiler automatically scales index by the size of the pointed-to type
        return arr[index];
    }

    bool isEmpty() const {
        return capacity == 0;
    }

    /**
     *  Add new element to the end of the vector.
     *
     * @param item integer value of the element to add
     */
    void push(int item) {
        if (size == capacity) {
            resize();
        }
        arr[size] = item;
        size++;
    }

    /**
     * Remove the last element from the vector.
     *
     * @return returns true if operation successful
     */
    bool pop() {
        if (size == 0) {
            throw std::out_of_range("Empty vector!");
        }
        // decrementing `size` is "logically" enough but zeroing for semantics...
        arr[size - 1] = 0;
        size--;
        return true;
    }


    /**
     * Insert an element into the given index.
     *
     * @param index integer value of index
     * @param item value of item to insert.
     */
    void insert(int index, int item) {
        if (index < 0 || size < index) {
            throw std::out_of_range("index out of range");
        }

        if (size == capacity) {
            resize();
        }

        // Shift the elements from 'size - 1' down to 'index' to the right to avoid overwriting
        for (int i = size; i > index; --i) {
            arr[i] = arr[i - 1];
        }
        *(arr + index) = item;
        size++;
    }

    /**
     * Add element at the start of the vector.
     *
     * @param value of element to add
     */
    void prepend(int value) {
        insert(0, value);
    }

    /**
     * Remove element at given index and shift all trailing elements.
     *
     * @param index of element to delete
     */
    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("index out of range");
        }

        // Shift elements from 'index + 1' to 'size - 1' to the left, because last to shift is arr[size -1]
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    /***
     * Remove all instances of given element from vector.
     *
     * @param value to be removed
     */
    void remove(int value) {
        for (int i = 0; i < size; i++) {
            if (*(arr + i) == value) {
                deleteAt(i);
                i--; // to check shifted index on next iteration
            }
        }
    }

    /**
     * Find first index of a target element.
     *
     * @param value of element to find
     * @return integer index of first instance found
     */
    int find(int value) const {
        for (int i = 0; i < size; i++) {
            if (*(arr + i) == value) {
                return i;
            }
        }
        return -1;
    }
};
