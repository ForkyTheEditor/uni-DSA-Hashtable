#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
typedef int TElem;
class SetIterator;

struct Node {

    TElem key;
    Node* next;

    Node();
    Node(TElem newKey);

};


class Set {
	//DO NOT CHANGE THIS PART
	friend class SetIterator;

    private:
		//TODO - Representation

        //array of pointers to the elements' linked lists
        Node** elements;

        //capacity of the set
        int m_cap;
        //the size of the set
        int setSize;

        //the hashfunction of the hashtable
        int hash(TElem elem, int m) const;
        //Converts the TElem to a natural number for the hash function to use
        //Can be updated to support more data types
        int convertToNatural(TElem elem) const;


    public:
        //implicit constructor
        Set();

        //adds an element to the set
		//returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
        bool add(TElem e);

        //removes an element from the set
		//returns true if e was removed, false otherwise
        bool remove(TElem e);

        //checks whether an element belongs to the set or not
        bool search(TElem elem) const;

        //returns the number of elements;
        int size() const;

        //check whether the set is empty or not;
        bool isEmpty() const;

        //return an iterator for the set
        SetIterator iterator() const;

        // destructor
        ~Set();

};





