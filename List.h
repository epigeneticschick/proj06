/*List.h adds functionality to a list
 * List.h
 * Lorrayya Williams and Andrew Baker
 *  Created on: Oct 9, 2018
 *      Author: llw5
 */

#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>

using namespace std;

template <class Item>

class List {
public:
	List();
	unsigned getSize() const;
	Item getFirst() const;
	Item getLast() const;
	void append(const Item& it);
	~List();
	List(const List& original);
	 List& operator=(const List& original);
	 bool operator!=(const List& original);
	 void writeTo(ostream& out, char sep) const;
	 void readFrom(const string& fileName);
	 unsigned getIndexOf(unsigned value);
	 Item remove(int index);
	 bool operator==(const List& next);
	 void readFrom(istream& in);
	 void writeTo(const string& fileName, char sep) const;
	 void prepend(const Item& pre);
	 void insert(const Item& add, unsigned index);
	 bool insertAfter(Item otherName, Item yourName);
	 bool insertBefore(Item otherName,Item yourName);


private:
	struct Node {
	Item myItem;
	Node*myNext;
	Node();
	Node(Item it, Node*next);
	~Node();
	};

	unsigned mySize;
	Node * myFirst;
	Node * myLast;
	friend class ListTester;
};

//Default Constructor
template <class Item>
List<Item>::List(){
	mySize = 0;
	myFirst = NULL;
	myLast = NULL;
}

//Default Node Constructor
template <class Item>
List<Item>::Node::Node() {
	myItem = Item();
	myNext = NULL;
}

//Node Constructor
template <class Item>
List<Item>::Node::Node(Item it, Node*next){
	myItem = it;
	myNext = next;

}

//Accessor for Size
template <class Item>
unsigned List<Item>::getSize() const{
	return mySize;
}

//Accessor for myFirst
template <class Item>
Item List<Item>::getFirst() const{
	if(mySize < 0 || myFirst == NULL){
		throw underflow_error("There is no First Node!");
	}
	else{
	return myFirst->myItem;
	}
}

//Accessor for myLast
template <class Item>
Item List<Item>::getLast() const{
	if(mySize < 0 || myFirst == NULL){
			throw underflow_error("There is no First Node!");
		}
		else{
		return myLast->myItem;
		}
}

//Appends the item to a list
template <class Item>
void List<Item>::append(const Item& it){
	 Node *nodePtr= new Node(it, NULL);
	if(myFirst == NULL){
		myFirst = nodePtr;

	}
	else{
		myLast->myNext = nodePtr;
	}
	myLast = nodePtr;
	mySize += 1;
}

// List Destructor
template <class Item>
List<Item>::~List() {
   delete myFirst;          // delete first node, invoking ~Node() (does nothing if myFirst == NULL)
   myFirst = myLast = NULL; // clear myFirst and myLast (optional)
   mySize = 0;              // clear mySize (optional)
}

//Node Destructor
template <class Item>
List<Item>::Node::~Node() {
//	cout << "~Node() is deallocating the node containing item "
//	             << myItem << endl;
    delete myNext;       // delete the next node, invoking ~Node() in it
                      // (does nothing if myNext == NULL)
 }

//List Deep Copy Constructor
template <class Item>
List<Item>::List(const List& original) {
     myFirst = myLast = NULL;       //  set pointers
     mySize = 0;                    //   and size to 'empty' values
     Node* oPtr = original.myFirst; //  start at the first node
     while (oPtr != NULL) {         //  while there are nodes to copy:
        append(oPtr->myItem);       //   append the item in that node
        oPtr = oPtr->myNext;        //   advance to next node
     }
  }

//List deep assignment operator
template <class Item>
List<Item>& List<Item>::operator=(const List& original){
if (myFirst != original.myFirst){
	myFirst = myLast = NULL;       //  set pointers
	delete myFirst;
	mySize = 0;                    //   and size to 'empty' values
	     Node* nPtr = original.myFirst; //  start at the first node
	     while (nPtr != NULL) {         //  while there are nodes to copy:
	        append(nPtr->myItem);       //   append the item in that node
	        nPtr = nPtr->myNext;        //   advance to next node
	     }
}
	return *this;
}


/*Written by Lorrayya Williams
 * Performs inequality operation for list
 * Param: List
 * Return: boolean*/
template <class Item>
bool List<Item>::operator!=(const List& original){
	if(mySize == original.mySize){
		return false;
	}

	if(myFirst == original.myFirst) {
		if(myLast == original.myLast){
			Node* nPtr = myFirst;
			Node* nPtr2 = original.myFirst;
			while(nPtr != NULL){
				nPtr->myItem == nPtr2->myItem;
				nPtr = nPtr->myNext;

			}
		}

	}

	else {
		return true;
	}
}


/*Written by Lorrayya Williams
 * Writes values from a list to a file
 * Param:
 * Return: */
template <class Item>
void List<Item>::writeTo(ostream& out, char sep) const{
	Node *nPtr = myFirst;
	for(unsigned i= 0; i< mySize; i++){
		out << nPtr->myItem
				<< sep;
		nPtr= nPtr->myNext;
	}
	out <<endl;
}



/*Written by Lorrayya Williams
 * Reads values from a file
 * Param: fileNAme
 * Return: in */
template <class Item>
void List<Item>::readFrom(const string& fileName) {
	ifstream in(fileName.c_str());
	assert(in.is_open());
	Item it;
	while(!in.eof()){
		in >> it;
		append(it);
	}
	in.close();

}

/*Written by Lorrayya Williams
 *  Accessor for Index of Value
 * Param: Value
 * Return: unsigned integer which is index*/
template <class Item>
unsigned List<Item>::getIndexOf(unsigned value){
	Node* nPtr = myFirst;
	unsigned index = 0;
	while(nPtr != NULL){
		if(nPtr->myItem == value){
			return index;
		}
		nPtr = nPtr->myNext;
		index += 1;
	}

	throw invalid_argument("That number is not in the list!");


}

/*Written by Lorrayya Williams
 * Removes items from a list based upon index
 * Param: Index
 * Return: value of index*/
template <class Item>
Item List<Item>::remove(int index) {
	//removes a value from a list at index
	if (mySize == 0) {
		throw range_error("list is empty");
	}

	int intmySize;
	intmySize = mySize; //to get rid of compilation warnings
	Node *bremPtr = myFirst; //before remove
	Node *remPtr = myFirst; //remove
	Item val;

	if (index <= 0) {
		myFirst = remPtr->myNext;
		val = remPtr->myItem;
		mySize -= 1; //decrement size
		remPtr = NULL;
		delete remPtr; //delete node
		return val; //return val at index
	}

	if (index+1 >= intmySize) {
		remPtr = remPtr->myNext; //first increment of remPtr
		for (unsigned i=0; i != mySize-1; ++i) {
			remPtr = remPtr->myNext;
			bremPtr = bremPtr->myNext;
		}
		myLast = bremPtr;
		bremPtr->myNext = remPtr->myNext;
		//updates my last to the ptr before remove
		myLast->myItem = bremPtr->myItem;
		val = remPtr->myItem;
		remPtr = NULL;
		delete remPtr;
		mySize -= 1;
		return val;

	}
	else {
		remPtr = remPtr->myNext; //first increment of remPtr
		for (int i=0; i <= index; i++) {
			if (i == index-1) {
				//before rem idx to ptr after rem idx
				bremPtr->myNext = remPtr->myNext;
				val = remPtr->myItem;
				remPtr = NULL;
				delete remPtr;
				mySize -= 1;
				return val;
			}

			//increment each idx
			remPtr = remPtr->myNext;
			bremPtr = bremPtr->myNext;
		}
	}

	return myFirst->myItem; //returns myFirst if all else fails
}


/*
 * Written by Andrew Baker
 * Tests equality between to lists, returns true or false
 * Param: second List
 * Return: boolean
 */

template <class Item>
bool List<Item>::operator==(const List& next){
	if (mySize != next.mySize){
		return false;
	}
	Node* oPtr = myFirst;
	Node* nPtr = next.myFirst;
	while(nPtr){
		if(oPtr->myItem != nPtr->myItem){
			return false;
		}
		oPtr = oPtr->myNext;
		nPtr = nPtr->myNext;
	}
	return true;
}

/*
 * Written by Andrew Baker
 * Reads from stream, returns void
 * Param: stream type
 * Return: Void
 */
template <class Item>
void List<Item>::readFrom(istream& in) {
	Item it;
	while(in.peek() != '\n'){
		in >> it;
		append(it);

	}
}


/*
 * Written by Andrew Baker
 * Writes the contents of a list in to a file, separated by a chosen value
 * Param: String
 * Return: void
 */
template <class Item>
void List<Item>::writeTo(const string& fileName, char sep) const{
	ofstream fout(fileName.c_str());
	assert(fout.is_open());
	Node* ptr = myFirst;
	while(ptr){
		fout << sep << ptr->myItem;
		ptr = ptr->myNext;
	}
	fout << endl;
	fout.close();
}

/*
 * Written by Andrew Baker
 * adds node with item to the beginning of the list
 * Param: Item
 * Return: void
 */
template <class Item>
void List<Item>::prepend(const Item& pre){
	if (mySize == 0){
		append(pre);
	}
	else{
		myFirst = new Node(pre, myFirst);
		mySize++;
	}

}

/*
 * Written by Andrew Baker
 * Inserts Node with item at chosen index, if <0 prepends, if >mySize appends
 * Param: Item, unsigned
 * Return: void
 */
template <class Item>
void List<Item>::insert(const Item& add, unsigned index) {
	if (index >= mySize) {
		append(add);
	} else if (index <= 0) {
		prepend(add);
	} else {
		List<Item>::Node* nPtr = myFirst;
		for (unsigned u = 0; u < index - 1; u++) {
			nPtr = nPtr->myNext;
		}
		nPtr->myNext = new Node(add, nPtr->myNext);
		mySize++;
	}
}

/*Written by Lorrayya Williams
Inserts an Item after the a a particular item passed through parameters then it returns a boolean*/
template <class Item>
bool List<Item>::insertAfter(Item otherName,Item yourName){
	Node* nPtr = myFirst;
	for(int i=0; i <= mySize; i++){
		if(nPtr->myItem == otherName){
			insert(yourName, i+1);
			return true;
		}
		nPtr =nPtr->myNext;

	}
	return false;
}

/*Written by Lorrayya Williams
Inserts item before a particular item passed through parameters then it returns a boolean*/
template <class Item>
bool List<Item>::insertBefore(Item otherName,Item yourName){
	Node* nPtr = myFirst;
	for(int i=0; i <= mySize; i++){
		if(nPtr->myItem == otherName){
			insert(yourName, i);
			return true;
		}
		nPtr =nPtr->myNext;

	}
	return false;
}

//FIX ME
/*Written by Lorrayya Williams
Adds all items in a list to the ostream and returns that stream<<*/
template <class Item>
ostream& operator<<(ostream& out, const List<Item>& alist){
	alist.writeTo(out, '\t');
	return out;
}

#endif /* LIST_H_ */
