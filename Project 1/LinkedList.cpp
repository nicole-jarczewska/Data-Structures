#include <iostream>
#include <algorithm>
#include "LinkedList.hpp"

void create(int A[], int n) {
	int i;
	struct Node* t, * last;
	first = new Node;
	first->data = A[0];
	first->next = NULL;
	last = first;

	for (i = 1; i < n; i++) {
		t = new Node;
		t->data = A[i];
		t->next = NULL;
		last->next = t;
		last = t;

	}

}

int count(struct Node* l) {
	int sum = 0;
	while (l != 0) {
		l = l->next;
		sum++;
	}
	return sum;
}

void append_index(struct Node* p, int index, int x) {
	struct Node* t;

	if (index <0 || index > count(p)) {
		return;
	}
	t = new Node;
	t->data = x;

	if (index == 0) {
		t->next = first;
		first = t;
	}
	else {
		for (int i = 0; i < index - 1; i++) {
			p = p->next;
		}
		t->next = p->next;
		p->next = t;
		
	}
}

void add_back(int value) {
	Node* t = new Node;   
	t->data = value;       
	t->next = nullptr;    


	Node* p = first;       
	while (p->next != nullptr) { 
		p = p->next;
	}

	p->next = t;         
}

void add_front(int value) {
	Node* t = new Node;
	t->data = value;
	t->next = first;
	first = t;
}

int find_value(struct Node* p, int value) {
	int index = 0;
	while (p != nullptr) {
		if (p->data == value) {
			return index;
		}
		p = p->next;
		index++;
	}
	return -1; // Not found
}

void delete_first() {
	if (first == nullptr) {
		std::cout << "Brak elementów na liscie!" << std::endl;
		return;
	}

	Node* t = first;
	first = first->next;

	delete t;
}

void delete_last() {
	
	if (first == nullptr) {
		std::cout << "Lista jest pusta!" << std::endl;
		return;
	}

	
	if (first->next == nullptr) {
		delete first; 
		first = nullptr; 
		return;
	}

	
	Node* p = first;
	
	while (p->next != nullptr && p->next->next != nullptr) {
		p = p->next;
	}

	
	delete p->next;  
	p->next = nullptr; 
}

int delete_index(struct Node* p, int index) {
	struct Node* q;
	int x = -1;

	
	if (index < 1 || index > count(p)) {
		std::cout << "Nieprawidłowy indeks!" << std::endl;
		return -1;
	}

	
	if (index == 1) {
		q = first;
		x = first->data;
		first = first->next;
		delete q; 
		return x;
	}
	else {
		
		for (int i = 0; i < index - 1; i++) {
			p = p->next;
		}

		
		q = p->next;
		p->next = q->next; 
		x = q->data;
		delete q; 
		return x;
	}
}

void display(struct Node* p) {
	while (p != NULL) {
		std::cout << p->data << " -> ";
		p = p->next;
	}
	std::cout << "END";
}