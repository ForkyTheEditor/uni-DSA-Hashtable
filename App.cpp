#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
#include <assert.h>
using namespace std;




int main() {

	//UNIT TEST FOR GETDELETECURRENT
	Set s = Set();
	s.add(3);
	SetIterator it = s.iterator();
	assert(it.getDeleteCurrent() == 3);
	assert(s.size() == 0);
	s.add(4321);
	s.add(1111);
	it.first();
	it.getDeleteCurrent();
	it.getDeleteCurrent();
	assert(s.size() == 0);


	// /UNIT TEST FOR GETDELETECURRENT


	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");

}



