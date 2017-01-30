#include "FibonacciHeap.h"
#include <iostream>
#include <array>
#include <vector>
#include <chrono>
#include <ratio>
#include <fstream>
#include <string>


int main() {
	const int size = 2560000;
	std::ifstream infile("polish.dic");
	std::string line;
	std::vector<std::string>* vec = new std::vector<std::string>();
	int i = 0;
	while (std::getline(infile, line))
	{
		vec->push_back(line);
		i++;
		if (i == size) {
			break;
		}
	}

	std::cout << vec->size() << std::endl;
	std::random_shuffle(vec->begin(), vec->end());
	std::vector<std::string>* vec2 = new std::vector<std::string>(*vec);

	auto clock1 = std::chrono::high_resolution_clock::now();
	std::make_heap(vec->begin(), vec->end());
	std::sort_heap(vec->begin(), vec->end());
	auto clock2 = std::chrono::high_resolution_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(clock2 - clock1);
	std::cout << "Binary Heap: " << time_span.count() << " sekund." << std::endl;

	clock1 = std::chrono::high_resolution_clock::now();
	FibHeap<std::string> heap;
	for (auto i : *vec2) {
		heap.insert(i);
	}
	for (int i = 0; i < vec2->size(); i++) {
		if ((*vec)[i] != heap.extractMin()->key) {
			std::cout << "Niespojnosc danych !!!" << std::endl;
		}
	}
	clock2 = std::chrono::high_resolution_clock::now();
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(clock2 - clock1);
	std::cout << "Fibonacci Heap czas: " << time_span.count() << " sekund." << std::endl;



/*
	std::array<int, size>* a = new std::array<int, size>();
	
	for (int i = 0; i < a->size(); i++) {
		(*a)[i] = i;
	}
	std::random_shuffle(a->begin(), a->end());
	std::array<int, size>* b = new std::array<int, size>(*a);

	auto clock1 = std::chrono::high_resolution_clock::now();
	std::make_heap(a->begin(), a->end());
	std::sort_heap(a->begin(), a->end());
	auto clock2 = std::chrono::high_resolution_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(clock2 - clock1);
	std::cout << "Binary Heap: " << time_span.count() << " sekund." << std::endl; 

	clock1 = std::chrono::high_resolution_clock::now(); 
	FibHeap<int> heap;
	for (auto i : *b) {
		heap.insert(i);
	}
	for (int i = 0; i < b->size(); i++) {
		if ((*a)[i] != heap.extractMin()->key) {
			std::cout << "Niespojnosc danych !!!" << std::endl;
		}
	}
	clock2 = std::chrono::high_resolution_clock::now();
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(clock2 - clock1);
	std::cout << "Fibonacci Heap czas: " << time_span.count() << " sekund." << std::endl;  
	
	
	delete(a);
	delete(b); */
	delete vec;
	delete vec2;
	return 0;
}