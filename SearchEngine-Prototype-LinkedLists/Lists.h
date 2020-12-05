#include "Nodes.h"
#include <iostream>
using namespace std;

template <class T>
class TermList {
private:
	Term_Info<T>* head;
	Term_Info<T>* tail;
public:
	TermList();
	Term_Info<T>* GetHead();
	Term_Info<T>* GetTail();
	void SetHead(Term_Info<T>*);
	void SetTail(Term_Info<T>*);
	void AddNode(Term_Info<T>*); //Add new node to the term list
	void DisplayTermListData();
};

template <class T> TermList<T>::TermList() {
	head = nullptr;
	tail = nullptr;
}

//getters and setters for the lsit
template <class T> Term_Info<T>* TermList<T>::GetHead() { return head; }
template <class T> Term_Info<T>* TermList<T>::GetTail() { return tail; }
template <class T> void TermList<T>::SetHead(Term_Info<T>* head) { this->head = head; }
template <class T> void TermList<T>::SetTail(Term_Info<T>* tail) { this->tail = tail; }
template <class T> void TermList<T>::AddNode(Term_Info<T>* node) {
	//check if list is empty
	if (head == nullptr || tail == nullptr) {
		head = node;
		tail = head;
	}
	//if one element
	else if (head == tail) {
		head->SetNext(node);
		node->SetPrev(head);
		tail = node;
	}
	//for all other cases
	else {
		node->SetPrev(tail);
		tail->SetNext(node);
		tail = node;
	}
}

template <class T> void TermList<T>::DisplayTermListData() {
	Term_Info<T>* ptr = tail;
	while (ptr->GetPrev() != nullptr) {
		cout << ptr->GetData() << endl;
		ptr = ptr->GetPrev();
	}
	cout << ptr->GetData() << endl;
}

template <class T>
class DocList {
private:
	DocList<T>* head;
	DocList<T>* tail;
public:
	DocList();
	DocList<T>* GetHead();
	DocList<T>* GetTail();
	void SetHead(DocList<T>*);
	void SetTail(DocList<T>*);
	void AddNode(DocList<T>*); //Add new node to the term list
	void DisplayTermListData();
};

template <class T> DocList<T>::DocList() {
	head = nullptr;
	tail = nullptr;
}
template <class T> DocList<T>* DocList<T>::GetHead() { return head; }
template <class T> DocList<T>* DocList<T>::GetTail() { return head; }
template <class T> void DocList<T>::SetHead(DocList<T>* head) { this->head = head; }
template <class T> void DocList<T>::SetTail(DocList<T>* tail) { this->tail = tail; }
template <class T> void DocList<T>::AddNode(DocList<T>* node) {
	//check if list is empty
	if (head == nullptr || tail == nullptr) {
		head = node;
		tail = node;
	}
	//if one element
	else if (head == tail) {
		head->SetNext(node);
		node->SetPrev(head);
		tail = node;
	}
	//for all other cases
	else {
		tail->SetNext(node);
		node->SetPrev(tail);
		tail = node;
	}
}