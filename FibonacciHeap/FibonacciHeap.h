#pragma once
#include <cmath>
#include <vector>
#include <algorithm>

#define NODE FibNode<T>*
#define HEAP FibHeap<T>* 

template<typename T>
class FibHeap
{
	template<typename T>
	class FibNode
	{
		friend FibHeap;
		FibNode(T key)
			:key(key), mark(false), p(nullptr), left(this), right(this), child(nullptr), degree(-1)
		{
		}

		~FibNode()
		{
		}
	public:
		T key;
	private:
		FibNode *p;
		FibNode *left;
		FibNode *right;
		FibNode *child;
		int degree;
		bool mark;
	};

private:
	int n; //number of nodes
	FibNode<T>* min; //node with minimum value


public:
	FibHeap(): n(0), min(nullptr) {

	}


private:
	void addToRootList(FibNode<T>* x) {
		if (min == nullptr) {
			min = x;
			x->left = x->right = x;
		}
		else {
			if (min->left != nullptr) {
				min->left->right = x;
				x->left = min->left;
				x->right = min;
				min->left = x;
			}
			else {
				x->right = x->left = min;
				min->left = min->right = x;
			}
		}
	}

	void removeFromRoot(FibNode<T>* x) {
		if (x->left != nullptr) {
			x->left->right = x->right;
			x->right->left = x->left;
		}
		else {
			min = nullptr;
		}
	}

	int getRootCount() {
		int count = 1;
		FibNode<T>* x = min->right;
		while (x != min) {
			x = x->right;
			count++;
		}
		return count;
	}

public:
	NODE insert(T v) {
		FibNode<T>* x = new FibNode<T>(v);
		x->degree = 0;
		x->p = nullptr;
		x->child = nullptr;
		x->mark = false;
		if (min == nullptr) {
			min = x->left = x->right = x;
		}
		else {
			min->left->right = x;
			x->left = min->left;
			min->left = x;
			x->right = min;
			if (x->key < min->key)
			{
				min = x;
			}
		}
		n++;
		return x;
	}

	HEAP heapUnion(HEAP h1, HEAP h2) {
		FibHeap *h = makeHeap();
		h.min = h1->min;
		FibNode* temp1 = h1->min->right;
		FibNode* temp2 = h2->min->left;
		h1->min->right = h2->min;
		h2->min->left = h1->min;
		temp1->left = temp2;
		temp2->right = temp1;
		if (h1->min == nullptr || (h2->min != nullptr && h2->min->key < h1->min->key )) {
			h->min = h2->min;
		}
		h.n = h1->n + h2->n;
		return h;
	}

private:
	void link(FibNode<T>* y, FibNode<T>* x) {
		removeFromRoot(y);
		if (x->child != nullptr) {
			y->left = x->child->left;
			y->right = x->child;
		}
		else {
			y->right = y->left = y;
		}
		x->child = y;
		if (y->left != nullptr) {
			y->left->right = y;
		}
		if (y->right != nullptr) {
			y->right->left = y;
		}
		x->degree++;
		y->mark = false;
	}

	void consolidate() {
		int max_degree =  std::floor(std::log(n) / std::log((1 + std::sqrt(5))/ 2.0));
		int d;
		FibNode<T> **B = (FibNode<T>**)malloc(max_degree*sizeof(FibNode<T>*));
		for (int i = 0; i < max_degree; i++) {
			B[i] = nullptr;
		}
		FibNode<T> *w, *x, *y, *nextW;
		int count = getRootCount();
		w = min;
		while(count > 0) {
			x = w;
			nextW = w->right;
			d = x->degree;
			while(d < max_degree - 1 && B[d] != nullptr) {
				y = B[d];
				if (x->key > y->key) {
					FibNode<T> *tmp = x;
					x = y;
					y = tmp;	
				}
				link(y, x);		
				B[d] = nullptr;
				d++;
			}
			B[d] = x;
			w = nextW;
			count--;
		}
		min = nullptr;

		for (int i = 0; i < max_degree; i++) {
			if (B[i] != nullptr) {
				if (min == nullptr) {
					B[i]->left = B[i]->right = B[i];
					min = B[i];
				}
				else {
					min->left->right = B[i];
					B[i]->left = min->left;
					B[i]->right = min;
					min->left = B[i];
					if (B[i]->key < min->key) {
						min = B[i];
					}
				}
			}
		}
		free(B);
	}

public:
	NODE extractMin() {
		FibNode<T>* z = min;
		if (z != nullptr) {
			FibNode<T>* next = z->child;
			if (next != nullptr) {
				FibNode<T>* x = next;
				FibNode<T>* initiial = x;
				do {			
					next = next->right;
					addToRootList(x);
					x->p = nullptr;
					x = next;
				} while (x != initiial);
			}
				
			removeFromRoot(z);

			if (z == z->right) {
				min = nullptr;
			}
			else {
				min = z->right;
				consolidate();
			}
			n--;
		}
		return z;
	}

private:
	void cut(FibNode<T>* x, FibNode<T>* y) {
		if (x->left != nullptr) {
			x->left->right = x->right;
		} 
		if (x->right != nullptr) {
			x->right->left = x->left;
		}
		if (y->child == x) {
			y->child = x->right;
		}
		if (min->left != nullptr) {
			min->left->right = x;
		}
		addToRootList(x);
		y->degree--;
		x->p = nullptr;
		x->mark = false;
	}

	void cascadingCut(FibNode<T>* y) {
		FibNode<T>* z;
		z = y->p;
		if (z != nullptr) {
			if (!y->mark) {
				y->mark = true;
			}
			else {
				cut(y, z);
				cascading(z);
			}
		}
	}

public:
	NODE decreaseKey(NODE x, T k) {
		if (k > x->key) {
			return; //ERROR
		}
		x->key = k;
		FibNode<T>* y = x->p;
		if (y != nullptr && x->key < y->key) {
			cut(x, y);
			cascadingCut(y);
		}
		if (x->key < min->key) {
			min = x;
		}
		return x;
	}

	NODE getMin() {
		return min;
	}

	void remove(NODE x) {
		decreaseKey(x, min);
		extractMin();
	}
};