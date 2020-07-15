#include "SetIterator.h"
#include "Set.h"
#include <iostream>

SetIterator::SetIterator(const Set& m) : set(const_cast<Set&>(m))
{	//BC: O(1) WC:O(m_cap) AC:O(1) amortized
	//TODO - Implementation
	index = 0;
	
	//Find the first valid element of the set
	while (index < set.m_cap && set.elements[index]->key == NULL_TELEM) {
		index += 1;
	}
	if (index < set.m_cap) {
		//There is an element
		//Index is now set to its position and currentNode is a reference to the head
		currentNode = set.elements[index];
	}
	else {
		//Set is empty
		currentNode = nullptr;
	}
	

}


void SetIterator::first() {
	//TODO - Implementation
	//BC: O(1) WC:O(m_cap) AC:O(1) amortized
	

	index = 0;

	//Find the first valid element of the set
	while (index < set.m_cap && set.elements[index]->key == NULL_TELEM) {
		index += 1;
	}
	if (index < set.m_cap) {
		//There is an element
		//Index is now set to its position and currentNode is a reference to the head
		currentNode = set.elements[index];
	}
	else {
		//Set is empty
		currentNode = nullptr;
	}


}


void SetIterator::next() {
	//TODO - Implementation
	//BC:O(1) WC:O(m) AC:O(1) amortized

	//Check for validity first
	if (this->valid()) {

		//Check if there are more elements in the linked list
		if (currentNode->next != nullptr) {
			//There are more elements, iterate over them
			currentNode = currentNode->next;
		}
		else {
			//There are no other elements, increase the index
			index += 1;

			//Run through the list, find the next valid location
			while (index < set.m_cap && set.elements[index]->key == NULL_TELEM) {
				index += 1;
			}
			//Check why it exited the loop
			//Is this a valid position?
			if (index < set.m_cap) {
				currentNode = set.elements[index];
			}
			else {
				//There were no more elements
				currentNode = nullptr;
			
			}


		}
	}
	else {

		//This isn't a valid position
		//throw an exception
		std::exception e;
		throw e;
	}

}


TElem SetIterator::getCurrent()
{
	//TODO - Implementation
	//BC/WC/AC: O(1)

	//Check if the current node is valid
	if (this->valid()) {

		return currentNode->key;
	}
	else {
		//throw an exception
		std::exception e;
		throw e;
	}

	return NULL_TELEM;
}
//Returns the current element in the iterator and deletes it
//Also calls Next() to avoid any problems;
TElem SetIterator::getDeleteCurrent()
{	//BC: O(1) WC:() AC:O()
	
	//Check for validity of current
	if (this->valid()) {
		//Get the current elem
		TElem returnElem = this->getCurrent();

		//Call next to avoid staying on an invalid bit
		this->next();

		//Remove it from the set
		set.remove(returnElem);

		//Return the element
		return returnElem;
	}
	else {
		//Not a valid location!
		std::exception e;
		throw e;

	}

	return NULL_TELEM;
	
}

bool SetIterator::valid() const {
	//TODO - Implementation

	//Check if the current node exists
	if (currentNode != nullptr && currentNode->key != NULL_TELEM) {
		return true;
	}


	return false;
}



