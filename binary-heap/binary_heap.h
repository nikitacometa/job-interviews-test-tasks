#pragma once

#include <vector>

template<class T> class binary_heap {
private:
    std::vector<T> data;

    void sift_up(unsigned int id);

    void sift_down(unsigned int id);

public:
    binary_heap() = default;

    explicit binary_heap(int capacity);

    void push(T const&);

    T& pop();

    T peek() const;

    int size() const;

    bool empty() const;
};

template <class T> void binary_heap<T>::sift_up(unsigned int id) {
    while (id > 0) {
        unsigned int parent = (id - 1) / 2;
        if (data[parent] > data[id]) {
            std::swap(data[parent], data[id]);
        }
        id = parent;
    }
}

template <class T> void binary_heap<T>::sift_down(unsigned int id) {
    while (true) {
        unsigned int child = id * 2 + 1;
        if (child >= data.size()) {
            break;
        }
        if (child + 1 < data.size() && data[child + 1] < data[child]) {
            child++;
        }
        if (data[child] < data[id]) {
            std::swap(data[child], data[id]);
            id = child;
        } else {
            break;
        }
    }
}

template <class T> binary_heap<T>::binary_heap(int capacity) {
    data.reserve(capacity);
}

template <class T> void binary_heap<T>::push(T const& value) {
    data.push_back(value);
    sift_up(data.size() - 1);
}

template <class T> T& binary_heap<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Error: popping element from an empty heap.\n");
    }

    std::swap(data[0], data[data.size() - 1]);
    T *res = &data[data.size() - 1];
    data.pop_back();
    sift_down(0);

    return *res;
}

template <class T> T binary_heap<T>::peek() const {
    if (empty()) {
        throw std::runtime_error("Error: peeking element from an empty heap.\n");
    }

    return data[0];
}

template <class T> int binary_heap<T>::size() const {
    return data.size();
}

template <class T> bool binary_heap<T>::empty() const {
    return data.empty();
}
