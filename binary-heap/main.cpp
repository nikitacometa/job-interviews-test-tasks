#include <iostream>

#include "binary_heap.h"

void run() {
    int n;
    std::cin >> n;
    binary_heap<std::string> heap(10);
    for (int i = 0; i < n; i++) {
        std::string x;
        std::cin >> x;
        heap.push(x);
    }

    std::cout << "\nHeap size: " << heap.size() << std::endl;
    std::cout << "The least element in the heap: " << heap.peek() << std::endl;
    std::cout << "Elements of the heap in ascending order:\n";
    while (!heap.empty()) {
        std::cout << heap.pop() << std::endl;
    }
}

int main() {
    try {
        run();
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
    }

    return 0;
}
