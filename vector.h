//
// Created by molder on 11/27/22.
//

#ifndef PETERTOWN_VECTOR_H
#define PETERTOWN_VECTOR_H

#include "algorithm"

template<typename T> class Vector {
private:
    T* items = nullptr;
    int size;
public:
    T *getItems() const;

private:
    int capacity;
    static const int MIN_CAPACITY = 8;
public:
    Vector();
    ~Vector();
    Vector(const Vector<T>& other);
    Vector<T>& operator= (const Vector<T>& other);
    Vector(int _capacity);

    T& operator[] (int pos) {return items[pos];};

    T* begin() const {return items;};
    T* end() const {return items + size;};

    void push(int pos, const T& item);
    void push_back(const T& item) {push(size, item);};

    T remove(int pos);
    T pop() { remove(size);};

    T* find(const T& item) const;

    int getSize() {return size;};

    void resize(int new_size);
};

template<typename T> Vector<T>::Vector(int _capacity):
        capacity(_capacity), size(0), items(new T[_capacity]) {}

template<typename T> Vector<T>::Vector(): Vector(MIN_CAPACITY) {}

template<typename T> Vector<T>::~Vector() {
    delete[] items;
}

template<typename T> Vector<T>& Vector<T>::operator= (const Vector<T>& other) {
//    *this = Vector<T>(other.capacity);
    delete[] items;
    items = new T[other.capacity];
    capacity = other.capacity;
    size = other.size;
    for (int i = 0; i < other.size; ++i) {
        items[i] = other.items[i];
    }
    return *this;
}

template<typename T> Vector<T>::Vector(const Vector<T>& other) {
    *this = other;
}

template<typename T> T* Vector<T>::find(const T& item) const {
    for (auto it = begin(); it != end(); ++it) {
        if (*it == item)
            return it;
    }
    return end();
}

template<typename T> void Vector<T>::push(int pos, const T &item) {
    if (size == capacity) {
        capacity *= 2;
        *this = Vector<T>(*this); //reallocate memory
    }
    for (int i = size; i > pos; --i) {
        items[i] = items[i - 1];
    }
    items[pos] = item;
    size++;
}

template<typename T> T Vector<T>::remove(int pos) {
    T deleted = items[pos];
    for (int i = pos; i < size; ++i) {
        items[i] = items[i + 1];
    }
    size--;

    if (size < capacity / 2 && capacity / 2 >= MIN_CAPACITY) {
        capacity /= 2;
        *this = Vector<T>(*this);
    }

    return deleted;
}

template<typename T>
void Vector<T>::resize(int new_size) {
    Vector<T> new_vector = Vector<T>(new_size);
    for (int i = 0; i < std::min(size, new_size); ++i) {
        new_vector[i] = items[i];
    }
    new_vector.size = new_size;
    *this = new_vector;
}

#endif //PETERTOWN_VECTOR_H
