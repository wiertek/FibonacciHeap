#include "FibonacciHeap.h"
#include <iostream>

int main() {
	FibHeap<int> heap;
	heap.insert(2);
	heap.insert(30);
	heap.insert(5);
	heap.insert(1);
	heap.insert(23);
	auto h = heap.extractMin();
	std::cout << "min: " << h->key << std::endl;
	return 0;
}