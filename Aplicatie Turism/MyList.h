#pragma once

template < typename T > class Iterator;

template < typename T > class List {
	friend class Iterator<T>;
private:
	class Node {
	private:
		T value;
		Node* next;
	public:
		//Constructor
		Node() : next{ nullptr } {
		}

		//Constructor with given element and node
		Node(const T& element, Node* n) :value{ element }, next{ n } {
		}

		//Copy Constructor
		Node(const Node& n) :value{ n.value }, next{ n.next } {
		}

		//Getter for value
		const T& getValue() const {
			return value;
		}

		//Setter for value
		void setValue(const T& e) {
			value = e;
		}

		//Geter for next node
		Node* getNext() const{
			return next;
		}

		//Setter for next node
		void setNext(Node* newNext) {
			next = newNext;
		}
	};

	Node* head;
	Node* copy() const;


public:
	//Constructor
	List();

	//Copy Constructor
	List(const List & l);

	//Operator = override
	List& operator = (const List & l);

	//Destructor
	~List();

	//returns list size
	int size() const;

	//returns true if list is empty
	bool isEmpty() const;

	//returns element on given position
	T getElement(int position) const;

	//sets the element on a given position
	void setElement(int position, T e);

	//inserts an element on a position
	void insert(int i, T e);

	void push_back(T e);

	//removes an element from a given position
	T remove(const Iterator<T>& position);

	//deallocates the list
	void clear();

	//Iterator friend class
	friend class Iterator<T>;

	//returns iterator on the list
	Iterator<T> begin();

	//returns iterator on the end of the list
	Iterator<T> end();

	//returns iterator on the list
	Iterator<T> begin() const;

	//returns iterator on the end of the list
	Iterator<T> end() const;

	//Overload operator [] for selection by index
	T operator [](int number) const;

	//Sorting function
	void sort(bool(*cmp)(const T& a, const T& b));
};

template <typename T> class Iterator {
	friend class List<T>;
private:
	const List<T>* list;
	typename List<T>::Node* curNode;
public:
	//Iterator constructor
	Iterator(const List<T>* l) :list{ l }, curNode{ l->head } {
	}

	//Constructor for given list (Iterator on copy)
	Iterator(const List<T> &l) {
		list->head = l.copy();
		curNode = l.head;
	}

	//Overload operator != for use in foreach
	bool operator !=(const Iterator& other) {
		return other.curNode != curNode;
	}

	//Overload operator ++ for use in foreach(increment iterator -> next element)
	Iterator& operator ++() {
		next();
		return *this;
	}

	//Overload operator + for iterating over more than one element
	Iterator& operator +(int n) {
		while (n) {
			next();
			n--;
		}
		return *this;
	}

	//Overload operator * for getting the value referenced by iterator
	const T& operator *() {
		return element();
	}

	//Sets iterator on first element
	void first() {
		curNode = list->head;
	}

	//Moves iterator to next element
	void next() {
		curNode = curNode->getNext();
	}

	//Checks if iterator is valid
	bool valid() {
		return curNode != nullptr;
	}

	//Returns the element that the iterator points to
	const T& element() {
		return curNode->getValue();
	}

};

template <typename T> void List<T>::clear() {
	while (head != nullptr) {
		Node* aux = head;
		head = head->getNext();
		delete aux;
	}
}

template <typename T> typename List<T>::Node* List<T>::copy() const {
	if (head == nullptr)
		return nullptr;
	else
	{
		Node *newHead = new Node(head->getValue(), nullptr);
		Node *curNode = head->getNext();
		Node *newCrt = newHead;
		Node *temp;
		while (curNode != nullptr)
		{
			temp = new Node(curNode->getValue(), nullptr);
			newCrt->setNext(temp);
			newCrt = temp;
			curNode = curNode->getNext();
		}
		return newHead;
	}
}

template < typename T > List<T>::List() {
	head = nullptr;
}

template < typename T > List<T>::List(const List<T> &l) {
	head = l.copy();
}

template < typename T > List<T>::~List() {
	clear();
}

template < typename T > List<T> &List<T>::operator = (const List<T>& l) {
	if (this != &l) {
		clear();
		head = l.copy();
	}
	return *this;
}

template < typename T > Iterator<T> List<T>::begin() {
	return Iterator<T>(this);
}

template < typename T > Iterator<T> List<T>::end() {
	Iterator<T> it(this);
	while (it.valid()) {
		it.next();
	}
	return it;
}

template < typename T > Iterator<T> List<T>::begin() const {
	return Iterator<T>(this);
}

template < typename T > Iterator<T> List<T>::end() const {
	Iterator<T> it(this);
	while (it.valid()) {
		it.next();
	}
	return it;
}

template < typename T > bool List<T>::isEmpty() const {
	return head == nullptr;
}

template < typename T > void List<T>::sort(bool(*cmp)(const T& a, const T& b)) {
	bool sorted = true;
	do {
		sorted = true;
		Node* p = head;
		while (p->getNext() != nullptr) {
			if (!cmp(p->getValue(), p->getNext()->getValue())) {
				sorted = false;
				const T aux = p->getNext()->getValue();
				Node* next = p->getNext();
				next->setValue(p->getValue());
				p->setValue(aux);
			}
			p = p->getNext();
		}
	} while (!sorted);
}

template < typename T > int List<T>::size() const {
	int s = 0;
	Node *curNode = head;
	while (curNode != nullptr) {
		s++;
		curNode = curNode->getNext();
	}
	return s;
}

template < typename T > T List<T>::getElement(int position) const {
	Node *curNode = head;
	int j = 0;
	while (j < position) {
		curNode = curNode->getNext();
		j++;
	}
	return curNode->getValue();
}

template < typename T > void List<T>::setElement(int position, T e) {
	Node *curNode = head;
	int j = 0;
	while (j < position) {
		curNode = curNode->getNext();
		j++;
	}
	curNode->setValue(e);
}

template < typename T > void List<T>::insert(int position, T e) {
	Node *prec = nullptr;
	Node *curNode = head;
	int j = 0;
	while (j < position) {
		prec = curNode;
		curNode = curNode->getNext();
		j++;
	}
	Node *p = new Node(e, curNode);
	if (prec != nullptr){
		prec->setNext(p);
	}
	else {
		head = p;
	}
}

template < typename T > void List<T>::push_back(T e) {
	Node *curNode = head;
	while (curNode != nullptr && curNode->getNext() != nullptr) {
		curNode = curNode->getNext();
	}
	Node *p = new Node(e, nullptr);
	if (curNode != nullptr) {
		curNode->setNext(p);
	}
	else {
		head = p;
	}
}

template < typename T > T List<T>::remove(const Iterator<T>& position)
{
	Node *prev = nullptr;
	Node *curNode = head;

	while (curNode != position.curNode) {
		prev = curNode;
		curNode = curNode->getNext();
	}

	if (prev != nullptr){ 
		prev->setNext(curNode->getNext());
	}
	else {
		head = curNode->getNext();
	}

	T el = curNode->getValue();
	delete curNode;
	return el;
}

template < typename T > T List<T>::operator [](int number) const {
	Iterator<T>& result = this->begin() + number;
	return *result;
}