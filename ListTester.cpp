/* ListTester.cpp defines the test methods for class List.
 * Joel Adams, for CS 112 at Calvin College.
 * Lorrayya Williams and Andrew Baker
 */


#include "ListTester.h" // ListTester
#include "List.h"       // List
#include <iostream>     // cin, cout
#include <cassert>      // assert()
#include <cstdlib>      // exit()
#include <stdexcept>    // underflow_error
#include <fstream>
using namespace std;

void ListTester::runTests() {
	cout << "Running List<double> tests..." << endl;
	testDefaultConstructor();
	testNodeDefaultConstructor();
	testNodeExplicitConstructor();
	testAppend();
	testDestructor();
	testCopyConstructor();
//	testInequality();
//	testReadFromString();
//	testWriteToStream();
//	testGetIndexOf();
//	testRemove();
//	testAssignment();
//	testEquality();
//	//testReadFromStream();
//	testWriteToString();
//	testPrepend();
//	testInsert();
	testinsertAfter();
	testinsertBefore();
	testOutputoperation();
	cout << "All tests passed!" << endl;
}

void ListTester::testDefaultConstructor() {
	cout << "Testing List<double> default constructor... " << flush;
	List<double> aList;
	assert( aList.mySize == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeDefaultConstructor() {
	cout << "Testing Node default constructor... " << flush;
	List<double>::Node aNode;
	assert( aNode.myItem == double() );
	assert( aNode.myNext == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeExplicitConstructor() {
	cout << "Testing Node explicit constructor... " << flush;
	List<double>::Node n1(11, NULL);
	assert( n1.myItem == 11 );
	assert( n1.myNext == NULL );
	cout << " 1 " << flush;

	List<double>::Node *n3 = new List<double>::Node(33, NULL);
	List<double>::Node n2(22, n3);
	assert( n2.myItem == 22 );
	assert( n2.myNext == n3 );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAppend() {
	cout << "Testing append()... " << flush;
	// empty List
	List<double> aList;
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	try {
		aList.getFirst();
		cerr << "getFirst() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0a " << flush;
	}
	try {
		aList.getLast();
		cerr << "getLast() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0b " << flush;
	}
	// append to empty list
	aList.append(11);
	assert( aList.getSize() == 1 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast == aList.myFirst );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 11 );
	assert( aList.myFirst->myNext == NULL );
	cout << " 1 " << flush;
	// append to a List<double> containing 1 Item
	aList.append(22);
	assert( aList.getSize() == 2 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.myFirst != aList.myLast );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 22 );
	assert( aList.myFirst->myNext != NULL );
	assert( aList.myLast->myNext == NULL );
	cout << " 2 " << flush;
	// append to a List<double> containing 2 Items
	aList.append(33);
	assert( aList.getSize() == 3 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 33 );
	assert( aList.myFirst->myNext->myItem == 22 );
	assert( aList.myLast->myNext == NULL );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testDestructor() {
	cout << "Testing destructor... " << flush;
	List<double> aList;
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 1 " << flush;

	aList.append(11);
	aList.append(22);
	aList.append(33);
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 2 " << flush;
	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testCopyConstructor() {
	cout << "Testing copy constructor... " << flush;
	// copy empty list
	List<double> list1;
	List<double> list2(list1);
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// copy nonempty list
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4(list3);
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}


/*Written by Lorrayya Williams
 * Tests Inequality Operator */
void ListTester::testInequality() {
	cout << "Testing Inequality operator... " << flush;

	//Intializes to empty list
	List<double> list1;
	List<double> list2;
	List<double> list3(list1);
	list2.append(11);
	assert(list1.getSize() == 0);
	assert(list1.myFirst == NULL);
	assert(list1.myLast == NULL);
	assert(list2.getSize() == 1);
	assert(list2.getFirst() == 11);
	assert(list2.getLast() == 11);
	cout << " 0 " << flush;


	assert(list1 != list2);
	assert( !(list1 != list3));
	cout << " 1 " << flush;
	cout << "Passed!" << endl;

}


/*Written by Lorrayya Williams
 * Tests ReadFromString */
void ListTester::testReadFromString(){
	cout << "Testing readFromString(filename)... " << flush;
	List<double> list1;
	List<double> list2;
	list2.append(1);
	list2.append(2);
	list2.append(3);
	list2.append(4);
	list2.append(5);
	list2.append(6);
	list2.append(7);
	list1.readFrom("test.txt");

	assert(list2.mySize == 7);
	assert(list2.getFirst() == 1);
	assert(list2.getLast() == 7);

	assert(list1.mySize == 7);
	assert(list1.getFirst() == 1);
	assert(list1.getLast() == 7);
	cout<< "0" << endl;

	List<double>::Node* nPtr = list1.myFirst;
	List<double>::Node* nPtr2 = list2.myFirst;
	while (nPtr != NULL){
		assert(nPtr->myItem == nPtr2->myItem);
		nPtr = nPtr2 = nPtr->myNext;
	}
	cout <<" 1 " << flush;

	//checks List<double> with more than one line in file
	List<double> list3;
	list3.readFrom("test1.txt");
	assert(list3.mySize == 14);
	assert(list3.getFirst() == 1);
	assert(list3.getLast() == 14);
	cout <<" 2 " << flush;

	list2.append(8);
	list2.append(9);
	list2.append(10);
	list2.append(11);
	list2.append(12);
	list2.append(13);
	list2.append(14);
	nPtr2 =list2.myFirst;
	nPtr = list3.myFirst;
	while (nPtr != NULL){
			assert(nPtr->myItem == nPtr2->myItem);
			nPtr = nPtr2 = nPtr->myNext;
		}
	cout << " 3 "<< flush;
	cout << "Passed!" << endl;
}


/*Written by Lorrayya Williams
 * Tess WriteToStream*/
void ListTester::testWriteToStream(){
	cout << "Testing writeTo(ostream)... " << flush;
	List<double> list1;
	list1.append(1);
	list1.append(2);
	list1.append(3);
	list1.append(4);
	ofstream fout("testwriteto.txt");
	assert( fout.is_open() );
	list1.writeTo(fout,'\t');
	fout.close();
	//assert(list1.mySize == 4);
	assert(list1.getFirst() == 1);
	assert(list1.getLast()== 4);
	cout << " 0 " << flush;

	List<double> list2;
	list2.append(1);
	list2.append(2);
	list2.append(3);
	list2.append(4);
	assert(list2.mySize == 4);
	assert(list2.getFirst() == 1);
	assert(list2.getLast()== 4);

	List<double>::Node* nPtr = list1.myFirst;
	List<double>::Node* nPtr2 = list2.myFirst;
	while (nPtr != NULL){
		assert(nPtr->myItem == nPtr2->myItem);
		nPtr = nPtr2 = nPtr->myNext;
	}
	cout << " 1 " << flush;


	cout << "Passed!" << endl;
}


/*Written by Lorrayya Williams
 * Tests Index Accessor*/
void ListTester::testGetIndexOf(){
	cout << "Testing Get Index Of... " << flush;
	List<double> list1;
	list1.append(1);
	list1.append(2);
	assert(list1.mySize == 2);
	assert(list1.getIndexOf(1) == 0);
	assert(list1.getIndexOf(2)== 1);
	cout << " 0 " << flush;

	List<double> list2;
	list2.readFrom("test.txt");
	assert(list2.getIndexOf(6) == 5);
	assert(list2.getIndexOf(3) == 2);
	cout<<" 1 " << flush;

	list2.append(3);
	list1.append(1);
	assert(list2.getIndexOf(3) == 2);
	assert(list1.getIndexOf(1) == 0);

	cout << " 2 " << flush;

	cout << "Passed! " << endl;
}


/*Written by Lorrayya Williams
 * Tests Remove function*/
void ListTester::testRemove(){
	cout << "Testing Remove... " << flush;
	//removes first item
	List<double> list2;
	list2.append(1);
	list2.append(2);
	list2.append(3);

	list2.remove(0);

	assert(list2.mySize == 2);
	assert(list2.getFirst() == 2);
	assert(list2.getLast() == 3);
	cout << " 0 " << flush;

	//Removes second  Item
	List<double> list1;
	list1.append(1);
	list1.append(2);
	list1.append(3);
	assert(list1.mySize ==  3);
	assert(list1.getFirst()== 1);
	assert(list1.getLast() == 3);
	list1.remove(1);
	assert(list1.mySize == 2);
	assert(list1.getFirst()== 1);
	assert(list1.getLast() == 3);
	cout << " 1 " << flush;
	cout << "Passed! " << endl;
}


void ListTester::testEquality() {
	cout << "Testing equality operator... " << flush;
	//Default lists
	List<double> list1;
	List<double> list2;
	assert(list1 == list2);
	cout << " 0 " << flush;
	//Non-default equal lists
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4;
	list4 = list3;
	assert(list3 == list4);
	cout << " 1 " << flush;

	//Same size, different contents
	List<double> list5;
	list5.append(11);
	list5.append(22);
	list5.append(33);
	List<double> list6;
	list6.append(44);
	list6.append(55);
	list6.append(66);
	assert(!(list5 == list6));
	cout << " 2 " << flush;

	//Different lists
	List<double> list7;
	list7.append(11);
	list7.append(22);
	list7.append(33);
	List<double> list8;
	list8.append(44);
	list8.append(55);
	list8.append(66);
	list8.append(77);
	list8.append(88);
	assert(!(list7 == list8));
	cout << " 3 " << flush;

	cout << "Passed!" << endl;
}

void ListTester::testReadFromStream() {
	cout << "Testing read from stream... " << flush;
	ifstream fin("ListTest1.txt");
	assert(fin.is_open());
	List<double> stream;
	stream.readFrom(fin);

	List<double>::Node* nPtr = stream.myFirst;
	for (unsigned u = 1; u < stream.mySize; u++) {
		assert(nPtr->myItem == u * 11);

		nPtr = nPtr->myNext;
		cout << " " << u - 1 << " " << flush;

	}

	cout << "Passed!" << endl;
}

void ListTester::testWriteToString() {
	cout << "Testing write to string... " << flush;
	//Creates first list
	List<double> list1;
	list1.append(11);
	list1.append(22);
	list1.append(33);

	//Writes to file
	list1.writeTo("ListWrite.txt", ' ');

	//Reads file
	ifstream fin("ListWrite.txt");
	List<double> list2;
	list2.readFrom(fin);
	assert(list2.getSize() == 3);
	assert(list2.getFirst() == 11);
	assert(list2.getLast() == 33);
	assert(list2.myFirst->myNext->myItem == 22);


	cout << "Passed!" << endl;
}

void ListTester::testPrepend() {
	cout << "Testing prepend... " << flush;
	List<double> aList;
	// prepend to empty list
	aList.prepend(11);
	assert(aList.getSize() == 1);
	assert(aList.myFirst != NULL);
	assert(aList.myLast == aList.myFirst);
	assert(aList.getFirst() == 11);
	assert(aList.getLast() == 11);
	assert(aList.myFirst->myNext == NULL);
	cout << " 1 " << flush;
	// prepend to a List<double> containing 1 Item
	aList.prepend(22);
	assert(aList.getSize() == 2);
	assert(aList.myFirst != NULL);
	assert(aList.myLast != NULL);
	assert(aList.myFirst != aList.myLast);
	assert(aList.getFirst() == 22);
	assert(aList.getLast() == 11);
	assert(aList.myFirst->myNext != NULL);
	assert(aList.myLast->myNext == NULL);
	cout << " 2 " << flush;
	// prepend to a List<double> containing 2 Items
	aList.prepend(33);
	assert(aList.getSize() == 3);
	assert(aList.myFirst != NULL);
	assert(aList.myLast != NULL);
	assert(aList.getFirst() == 33);
	assert(aList.getLast() == 11);
	assert(aList.myFirst->myNext->myItem == 22);
	assert(aList.myLast->myNext == NULL);
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testInsert() {
	cout << "Testing insert... " << flush;
	List<double> aList;
	// insert to empty list
	aList.insert(11, 3);
	assert(aList.getSize() == 1);
	assert(aList.myFirst != NULL);
	assert(aList.myLast == aList.myFirst);
	assert(aList.getFirst() == 11);
	assert(aList.getLast() == 11);
	assert(aList.myFirst->myNext == NULL);
	cout << " 1 " << flush;
	// insert to a List<double> containing 1 Item
	aList.insert(22, 0);
	assert(aList.getSize() == 2);
	assert(aList.myFirst != NULL);
	assert(aList.myLast != NULL);
	assert(aList.myFirst != aList.myLast);
	assert(aList.getFirst() == 22);
	assert(aList.getLast() == 11);
	assert(aList.myFirst->myNext != NULL);
	assert(aList.myLast->myNext == NULL);
	cout << " 2 " << flush;
	// insert to a List<double> containing 2 Items
	aList.insert(33, 1);
	assert(aList.getSize() == 3);
	assert(aList.myFirst != NULL);
	assert(aList.myLast != NULL);
	assert(aList.getFirst() == 22);
	assert(aList.getLast() == 11);
	cout << aList.myFirst->myNext->myItem;
	assert(aList.myFirst->myNext->myItem == 33);
	assert(aList.myLast->myNext == NULL);
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAssignment() {
	cout << "Testing assignment... " << flush;
	// empty to empty assignment
	List<double> list1;
	List<double> list2;
	list2 = list1;
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// non-empty to empty assignment
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4;
	list4 = list3;
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myFirst->myNext != list3.myFirst->myNext );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;

	// equal-sized non-empty to non-empty assignment
	List<double> list5;
	list5.append(44);
	list5.append(55);
	list5.append(66);
	list5 = list3;
	assert( list5.getSize() == 3 );
	assert( list5.getFirst() == 11 );
	assert( list5.getLast() == 33 );
	assert( list5.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list5.myFirst != list3.myFirst );
	assert( list5.myFirst->myNext != list3.myFirst->myNext );
	assert( list5.myLast != list3.myLast );
	cout << " 3 " << flush;

	// empty to non-empty assignment
	List<double> list6;
	list6.append(44);
	list6.append(55);
	list6.append(66);
	List<double> list7;
	list6 = list7;
	assert( list6.getSize() == 0 );
	assert( list6.myFirst == NULL );
	assert( list6.myLast == NULL );
	cout << " 4 " << flush;

	// unequal-sized non-empty to non-empty assignment
	List<double> list8;
	list8.append(44);
	list8.append(55);
	list8.append(66);
	list8.append(77);
	list8 = list3;
	assert( list8.getSize() == 3 );
	assert( list8.getFirst() == 11 );
	assert( list8.getLast() == 33 );
	assert( list8.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list8.myFirst != list3.myFirst );
	assert( list8.myFirst->myNext != list3.myFirst->myNext );
	assert( list8.myLast != list3.myLast );
	cout << " 5 " << flush;

	// assignment chaining
	List<double> list9;
	list9.append(44);
	list9.append(55);
	list9.append(66);
	list9.append(77);
	List<double> list10;
	list10 = list9 = list8;
	assert( list10.getSize() == 3 );
	assert( list10.getFirst() == 11 );
	assert( list10.getLast() == 33 );
	assert( list10.myFirst->myNext->myItem == 22 );
	cout << " 6 " << flush;

	// self-assignment (stupid, but possible)
	List<double> list11;
	list11.append(11);
	list11.append(22);
	list11.append(33);
	list11 = list11;
	assert( list11.getSize() == 3 );
	assert( list11.getFirst() == 11 );
	assert( list11.getLast() == 33 );
	assert( list11.myFirst->myNext->myItem == 22 );
	cout << " 7 " << flush;

	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testinsertAfter(){
	cout << "Testing insertAfter ..." << flush;
	List<double> list1;
	list1.append(1);
	list1.append(2);
	list1.append(3);
	assert(list1.getSize() == 3);
	assert(list1.getFirst() == 1);
	assert(list1.getLast() == 3);
	cout << " 0 " << flush;

	//checks an item inserted after the first item
	List<double> list2;
	list2.append(1);
	list2.append(2);
	list2.append(3);
	list2.insertAfter(1,4);
	assert(list2.myFirst->myNext->myItem == 4);
	cout << " 1 " << flush;

	//checks an item inserted after the middle item
	List<double> list3;
	list3.append(1);
	list3.append(2);
	list3.append(3);
	list3.insertAfter(2,4);
	assert(list3.getSize()== 4);
	assert(list3.myFirst->myNext->myNext->myItem == 4);
	cout << " 2 " << flush;

	//checks an item inserted after the last item
	list1.insertAfter(3,4);
	assert(list1.getSize()== 4);
	assert(list1.getLast() == 4);
	cout <<" 3 " << flush;


	cout<< "Passed!" << endl;
}

void ListTester::testinsertBefore(){
	cout << "Testing insertBefore ... " << flush;
	//checks an item inserted before first item
	List<double> list1;
	list1.append(1);
	list1.append(2);
	list1.append(3);
	list1.insertBefore(1, 4);
	assert(list1.getSize()== 4);
	assert(list1.getFirst() == 4);
	cout << " 0 " << flush;

	//checks an item inserted before the second item
	List<double> list2;
	list2.append(1);
	list2.append(2);
	list2.append(3);
	list2.insertBefore(2,4);
	assert(list2.myFirst->myNext->myItem == 4);
	assert(list2.getSize() == 4);
	cout << " 1 " << flush;

	//checks an item inserted before the last itme
	List<double> list3;
	list3.append(1);
	list3.append(2);
	list3.append(3);
	list3.insertBefore(3,4);
	assert(list3.myFirst->myNext->myNext->myItem == 4);
	assert(list3.getSize() == 4 );
	cout<< " 2 " << flush;
	cout << "Passed!" << endl;
}

//FIX ME
void ListTester::testOutputoperation(){
	cout << "Testing Operation ... " << flush;

	//output an empty list
	List<double> list1;
	cout << list1;
	cout << " 0 " << flush;

	//output a non-empty list
	List<double> list2;
	list2.append(1);
	list2.append(2);
	list2.append(3);
	cout << list2;
	cout << " 1 "<< flush;

	cout << "Passed!" << endl;
}
