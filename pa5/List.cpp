/*
Ko-Wei Chang
kochang
pa5
*/

#include<string>
#include<cstring>
#include<iostream>
#include<stdexcept>
#include"List.h"

using namespace std;

// private Node struct
List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List(){
	frontDummy = new Node(0);
	backDummy = new Node(1);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
}

// Copy constructor.
List::List(const List& L){
	frontDummy = new Node(0);
	backDummy = new Node(1);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;

	Node* N = L.frontDummy->next;
	while(N != L.backDummy){
		this->insertBefore(N->data);
		N = N->next;
	}
	this->moveFront();
}

// Destructor
List::~List(){
	if(length() != 0){
		this->clear();
	}
	delete(frontDummy);
	delete(backDummy);
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
	return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
	if(length() <= 0){
		throw std::length_error("List: front(): empty list");
	}
	return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if(length() <= 0){
		throw std::length_error("List: back(): empty list");
	}
	return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
	if (position() >= length()){
		throw std::range_error("List: peekNext(): cursor at back");
	}
	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if (position() <= 0){
		throw std::range_error("List: peekPrev(): cursor at front");
	}
	return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	this->moveFront();
	while(length() != 0){
		this->eraseAfter();
	}
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
	pos_cursor = 0;
	afterCursor = frontDummy->next;
	beforeCursor = frontDummy;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
	pos_cursor = length();
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
	if(position() >= length()){
		throw std::range_error("List: moveNext(): cursor at back");
	} else {
		pos_cursor++;
		beforeCursor = beforeCursor->next;
		afterCursor = afterCursor->next;
		return beforeCursor->data;
	}
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
	if(position() <= 0){
		throw std::range_error("List: movePrev(): cursor at front");
	} else {
		pos_cursor--;
		beforeCursor = beforeCursor->prev;
		afterCursor = afterCursor->prev;
		return afterCursor->data;
	}
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
	Node* N = new Node(x);

	N->next = afterCursor;
	N->prev = beforeCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
	Node* N = new Node(x);

	N->next = afterCursor;
	N->prev = beforeCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	beforeCursor = N;
	num_elements++;
	pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
	if(position() >= length()){
		throw std::range_error("List: setAfter(): cursor at back");
	} else {
		afterCursor->data = x;
	}
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
	if(position() <= 0){
		throw std::range_error("List: setBefore(): cursor at front");
	} else {
		beforeCursor->data = x;
	}
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
	if(position() >= length()){
		throw std::range_error("List: eraseAfter(): cursor at back");
	} 	
	Node* N = afterCursor;
	afterCursor = afterCursor->next;
	beforeCursor->next = afterCursor;
	afterCursor->prev = beforeCursor;
	delete N; 
	num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if(position() <= 0){
		throw std::range_error("List: eraseBefore(): cursor at front");
	} 	
	Node* N = beforeCursor;
	beforeCursor = beforeCursor->prev;
	afterCursor->prev = beforeCursor;
	beforeCursor->next = afterCursor;
	delete N; 
	num_elements--;
	pos_cursor--;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
	while(afterCursor != backDummy){
		if (afterCursor->data == x){
			this->moveNext();
			return position();
		}
		this->moveNext();
	}
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
	while(beforeCursor != frontDummy){
		if (beforeCursor->data == x){
			this->movePrev();
			return position();
		}
		this->movePrev();
	}
	return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
	Node* N = frontDummy->next;
	int tempCursor = 0; 
	int count = 0;
	int saveCursor = pos_cursor;
	while(N != backDummy){
		moveFront();
		findNext(N->data);
		//if (N->next != backDummy){
		while (tempCursor != -1 && N->next != backDummy){
			tempCursor = findNext(N->data);
			if (pos_cursor <= saveCursor){
				saveCursor--;
			}
			if (tempCursor != -1){
				eraseBefore();
			}
		}
		//}
		N = frontDummy->next;
		count++;
		for (tempCursor = 0; tempCursor < count; ++tempCursor)
		{
			N = N->next;
		}
	}
	moveFront();
	for (tempCursor = 0; tempCursor < saveCursor; ++tempCursor)
	{
		moveNext();
	}
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
	List K;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;
	while(N != this->backDummy){
		K.insertBefore(N->data);
		N = N->next;
	}
	while(M != L.backDummy){
		K.insertBefore(M->data);
		M = M->next;
	}
	K.moveFront();
	return K;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	string s = "(";
	Node* N = nullptr;
	for (N = frontDummy->next; N != backDummy->prev; N = N->next)
	{
		s += std::to_string(N->data) + ", ";
	}
	s += std::to_string(N->data);
	s += ")";
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;

	eq = (this->length() == R.length());
	N = this->frontDummy->next;
	M = R.frontDummy->next;
	while (eq && N!=this->backDummy){
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if (this != &L){
		List temp = L;
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(num_elements, temp.num_elements);
	}
	return *this;
}