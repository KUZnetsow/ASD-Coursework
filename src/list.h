#pragma once
#include <iostream>
#include "graph.h"
#ifndef LIST_H
#define LIST_H
template<class T>
class elem {
private:
	T inf;
	elem* next;
public:
	elem(T elem_inf) { inf = elem_inf; next = nullptr; }
	~elem() {};
	elem* getNext() { return next; }
	void setNext(elem* elem_next) { next = elem_next; }
	T getInf() { return inf; }
	T* getLink() { return &inf; }
	void setInf(T elem_inf) { inf = elem_inf; }
};

template<class T>
class list {
private:
	elem<T>* begin, * end;
	size_t size;
public:
	list() { begin = nullptr; end = nullptr; size = 0; }
	~list() { clear(); }

	//Adding new element to end of list
	void push_back(T temp) {
		elem<T>* newElem = new elem<T>(temp);
		if (isEmpty()) begin = newElem;
		else end->setNext(newElem);
		end = newElem;
		size++;
	}

	//Adding new element to begin of list
	void push_front(T temp) {
		elem<T>* newElem = new elem<T>(temp);
		if (isEmpty()) end = newElem;
		else newElem->setNext(begin);
		begin = newElem;
		size++;
	}

	//Deleting last element from list
	void pop_back() {
		if (!isEmpty()) {
			if (size == 1) {
				end = nullptr;
				begin = nullptr;
				size = 0;
			}
			else {
				elem<T>* newEnd = begin;
				while (newEnd->getNext() != end) newEnd = newEnd->getNext();
				newEnd->setNext(nullptr);
				elem<T>* deleted = end;
				delete deleted;
				end = newEnd;
				size--;
			}
		}
		else throw "List is Empty";
	}

	//Deleting first element from list
	void pop_front() {
		if (!isEmpty()) {
			if (size == 1) {
				begin = nullptr;
				end = nullptr;
				size = 0;
			}
			else {
				elem<T>* newBeg = begin->getNext();
				elem<T>* deleted = begin;
				delete deleted;
				begin = newBeg;
				size--;
			}
		}
		else throw "List is Empty";
	}

	//Adding element to any position in list
	void insert(T data, size_t pos) {
		if (pos <= size) {
			if (isEmpty() || pos == size) push_back(data);
			else {
				if (pos == 0) push_front(data);
				else {
					elem<T>* newElem = new elem<T>(data);
					elem<T>* iter = begin;
					while (pos-- > 1)
						iter = iter->getNext();
					newElem->setNext(iter->getNext());
					iter->setNext(newElem);
					size++;
				}
			}
		}
		else throw "Wrong index";
	}

	//Getting element from list by index
	T* at(size_t pos) {
		if (pos < size) {
			elem<T>* iter = begin;
			while (pos-- != 0) iter = iter->getNext();
			return iter->getLink();
		}
		else throw "Wrong index";
	}

	//Deleting element from list by index
	void remove(size_t pos) {
		if (pos < size) {
			if (pos == 0) pop_front();
			else {
				if (pos == size - 1) pop_back();
				else {
					elem<T>* iter = begin;
					while (pos-- > 1) iter = iter->getNext();
					elem<T>* nextElem = iter->getNext();
					iter->setNext(nextElem->getNext());
					size--;
				}
			}
		}
		else throw "Wrong index";
	}

	//Getting size of list
	size_t getSize() { return size; }

	//Output elements from list to console
	void print_to_console() {
		elem<T>* iter = begin;
		for (size_t i = 0; i < size; i++) {
			std::cout << iter->getInf() << " ";
			iter = iter->getNext();
		}
	}

	//Deleting elements of list
	void clear() {
		while (size) pop_back();
	}

	//Replacing element by index with new one
	void set(size_t pos, T data) {
		if (pos < size) {
			elem<T>* iter = begin;
			while (pos-- != 0) iter = iter->getNext();
			iter->setInf(data);
		}
		else throw "Wrong index";
	}

	//Checking list for filling
	bool isEmpty() {
		if (size == 0) return true; // 1 - Empty
		else return false;			// 0 - Filled
	}

	//Adding another list to front of this one
	void push_front(list* lst) {
		for (size_t i = 0; i < lst->getSize(); i++)
			insert(lst->at(i), i);
	}

	//return last element in list
	T back() {
		return end->getInf();
	}

	//find element in list
	bool contain(T toFind) {
		elem<T>* temp = begin;
		while (temp != nullptr) {
			if (temp->getInf() == toFind) return true;
			temp = temp->getNext();
		}
		return false;
	}

	int indexOf(T toFind) {
		elem<T>* temp = begin;
		int i = 0;
		while (temp != nullptr) {
			if (temp->getInf() == toFind) return i;
			temp = temp->getNext();
			i++;
		}
		return -1;
	}
};
#endif