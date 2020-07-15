#pragma once
#include "Set.h"

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	Set& set;
	SetIterator(const Set& s);

	//TODO - Representation
	int index;
	Node* currentNode;


public:
	void first();
	void next();
	TElem getCurrent();
	TElem getDeleteCurrent();
	bool valid() const;
};


