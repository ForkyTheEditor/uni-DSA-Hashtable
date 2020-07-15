#include "Set.h"
#include "SetITerator.h"
#include <cmath>

Node::Node() {

	key = NULL_TELEM;
	next = nullptr;

}

Node::Node(TElem newKey) {

	this->key = newKey;
	this->next = nullptr;
}

Set::Set() {
	//TODO - Implementation
	//BC/WC/AC: O(m_cap) (17) (aber jedoch konstant)

	//it's best if m is a prime number (because of its use in the hash function)
	m_cap = 17;
	setSize = 0;
	
	//Initialize the array of pointers
	elements = new Node*[m_cap];
	for (int i = 0; i < m_cap; i++) {
		
		elements[i] = new Node();

	}


}

int Set::convertToNatural(TElem elem) const {

	//only int for now
	int returnValue = elem;

	return returnValue;
	
}

int Set::hash(TElem elem, int m) const{
	//Multiplication method
	//hash(k)= ⌊m(kA mod 1)⌋
	//A - constant between (0,1)
	double A = 0.6180339887;

	int k = convertToNatural(elem);

	double kA = k * A;

	double intPart = 0;
	double fractionalPart = 0;
	
	//Get the absolute value of this (for elements that are <0)
	fractionalPart = std::abs(std::modf(kA, &intPart));
	
	int returnValue = m *  fractionalPart; 

	
	return returnValue;
}

bool isPrime(int n)
{
	// Corner case 
	if (n <= 1)
		return false;
	
	// Check from 2 to n-1 
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return false;

	return true;
}

//Given an integer n gives the next prime after it
int findNextPrime(int n){

	int current = n;
	while (!isPrime(current)) {

		current += 1;
	}

	return current;
}

bool Set::add(TElem elem) {
	//TODO - Implementation
	//Check if the element is already in the list
	//BC: O(1) WC:O(n) AC:O(1) amortized
	//Worst-case: Wenn man auch den Resize operation aufrufen muss

	if (search(elem)) {
		return false;
	}

	//Resize the container
	if (setSize >= m_cap) {

		int newCap = findNextPrime(3 * m_cap);
		Node** newElements = new Node*[newCap];

		//Initialize the new container
		for (int i = 0; i < newCap; i++) {

			newElements[i] = new Node();

		}
		SetIterator it = this->iterator();

		//Iterate through the old list and readd everything while rehashing
		while (it.valid()) {

			TElem newElem = it.getCurrent();
			int newPos = hash(newElem, newCap);
			Node* newNode = new Node(newElem);

			//Its a new position in the hash table
			if (newElements[newPos]->key == NULL_TELEM) {

				newElements[newPos] = newNode;

			}
			else {
				//Add to the head of the list
				newNode->next = newElements[newPos];
				newElements[newPos] = newNode;

			}
			
			//Iterate
			it.next();
		}

		m_cap = newCap;
		elements = newElements;
	}

	//Add the element normally
	int pos = hash(elem, m_cap);
	Node* newNode = new Node(elem);


	//Check if the position is empty (default constructor initializes it with NULL_TELEM)
	//The element is bound to be unique
	//The element is now the head of the list
	if (elements[pos]->key == NULL_TELEM) {

		elements[pos] = newNode;
		
		//Update the size of the set
		setSize += 1;

		return true;
	}
	else {
		//There is a collision!
		//The element isn't in the list, add it
		
		//Add the new element as the head of the list
		newNode->next = elements[pos];
		elements[pos] = newNode;

		//Update set size
		setSize += 1;


		return true;
	}
}


bool Set::remove(TElem elem){
	//TODO - Implementation
	//BC: O(1) WC:O(alfa) AC:O(1) amortized
	//wo alfa ist die Lange der Verkettete Liste
	//Im Allgemeinen sollten die Verketteten Listen relativ kurz sein => hat keinen grossen Impakt

	int pos = hash(elem, m_cap);

	if (!search(elem)) {
		return false;
	}

	if (elements[pos]->key == NULL_TELEM) {
		//The element isn't in the list
		return false;
	}
	else {

		//Check if it's the head of the list
		if (elements[pos]->key == elem) {
			//The element is the head

			//Check if it's the only element in the list
			if (elements[pos]->next == nullptr) {
				//There are no other elements, reset the head
				elements[pos]->key = NULL_TELEM;
			}
			else {
				//There are other elements in the linked list
				elements[pos] = elements[pos]->next;
			}

			//Update the size
			setSize -= 1;
			return true;
		}

		//Iterate through the linked list
		Node* currentNode = elements[pos];
		Node* previousNode = currentNode;

		//Iterate through the nodes until we find the good one or they end
		while (currentNode != nullptr && currentNode->key != elem) {

			previousNode = currentNode;
			currentNode = currentNode->next;
		}

		//Check why the loop ended
		if (currentNode != nullptr) {

			previousNode->next = currentNode->next;

			setSize -= 1;
			return true;
		}
		else {
			return false;
		}

	}
}

bool Set::search(TElem elem) const {
	//TODO - Implementation
	//BC: O(1) WC:O(alfa) AC:O(1) amortized
	//wo alfa ist die Lange der Verkettete Liste
	//Im Allgemeinen sollten die Verketteten Listen relativ kurz sein => hat keinen grossen Impakt
	int pos = hash(elem, m_cap);
	Node* currentNode = elements[pos];

	//Iterate through the entire list
	while (currentNode != nullptr && currentNode->key != elem) {
		currentNode = currentNode->next;
	}

	//Check if the element has been found
	//If the current node exists then it's because the element has been found
	if (currentNode != nullptr) {
		return true;
	}
	else {
		return false;
	}

}


int Set::size() const {
	//TODO - Implementation
	//BC/WC/AC: O(1)

	return setSize;
}


bool Set::isEmpty() const {
	//TODO - Implementation
	//BC/WC/AC: O(1)

	if (setSize == 0) {
		return true;
	}

	return false;
}


Set::~Set() {
	//TODO - Implementation
	//BC/WC/AC: O(1)

	delete elements;

}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


