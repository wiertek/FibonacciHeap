#include "FibonacciHeap.h"
#include <iostream>
#include <array>
#include <chrono>
#include <ratio>



int main() {
	constexpr int size = 100;
	std::array<int, size> a;
	for (int i = 0; i < a.size(); i++) {
		a[i] = i;
	}
	std::random_shuffle(a.begin(), a.end());
	std::array<int, size> b(a);

	auto clock1 = std::chrono::high_resolution_clock::now();
	std::make_heap(a.begin(), a.end());
	std::sort_heap(a.begin(), a.end());
	auto clock2 = std::chrono::high_resolution_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(clock2 - clock1);
	std::cout << "BST: " << time_span.count() << " sekund." << std::endl;

	clock1 = std::chrono::high_resolution_clock::now();
	FibHeap<int> heap;
	for (auto i : b) {
		heap.insert(i);
	}
	for (int i = 0; i < b.size(); i++) {
		heap.extractMin()->key;
	}
	clock2 = std::chrono::high_resolution_clock::now();
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(clock2 - clock1);
	std::cout << "Fibonacci Heap: " << time_span.count() << " sekund." << std::endl;
	
/*	for (const auto &i : a) {
		std::cout << i << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < b.size(); i++) {
		std::cout << heap.extractMin()->key << " ";
	} */
	

	return 0;
}