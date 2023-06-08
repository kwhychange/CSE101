/*
Ko-Wei Chang
kochang
pa8
*/

#include "Dictionary.h"
#include<iostream>
#include<string>
#include<stdexcept>

#define RED -1
#define BLACK -2

using namespace std;

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if(R != nil){
		inOrderString(s, R->left);
		s.append(R->key + " : " + std::to_string(R->val) + "\n");
		inOrderString(s, R->right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string will consist of keys only, with the order determined by a pre-order
// tree walk. The keys stored in black Nodes will be appended as "key\n", and
// the keys stored in red Nodes will be appended as "key (RED)\n". The output 
// of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != nil){
		if (R->color == RED){ 
			s.append(R->key + " (RED)\n");
		} else {
			s.append(R->key + "\n");
		}
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
void Dictionary::BST_insert(Node* M){
	// Node* X = root;
	// Node* Y = nil;
	// M->right = M->left = nil;
	// M->color = RED;

	// while(X != nil){
	// 	Y = X;
	// 	if (M->key < X->key){
	// 		X = X->left;
	// 	} else {
	// 		X = X->right;
	// 	}
	// }
	// M->parent = Y;
	// if(Y == nil){
	// 	root = M;
	// 	num_pairs++;
	// } else if (M->key < Y->key){
	// 	Y->left = M;
	// 	num_pairs++;
	// } else if (M->key > Y->key){
	// 	Y->right = M;
	// 	num_pairs++;
	// } 
	// RB_InsertFixUp(M);
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
	if(R != N){
		// BST_insert(R);
		setValue(R->key, R->val);
		cout << R->key << " key " << R->color << "col" << endl;
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
	if(R != nil){
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		R->parent = R->left = R->right = nullptr;
		delete R;
		num_pairs--;
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if (R == nil){
		return nil;
	} else if (k == R->key){
		return R;
	} else if (k < R->key){
		return search(R->left, k);
	} else if (k > R->key){
		return search(R->right, k);
	}
	return nil;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
	if(R == nil){
		throw logic_error("Dictionary: findMin(): subtree given is rooted at nil");
	}
	while(R->left != nil){
		// cout << R->left->key << " R "<< R->right->key << " P "<< R->parent->key << endl;
		// cout << R->left->left->key << endl;
		R = R->left;
	}
	return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
	if(R == nil){
		throw logic_error("Dictionary: findMax(): subtree given is rooted at nil");
	}
	while(R->right!= nil){
		R = R->right;
	}
	return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	if(N->right != nil){
		return findMin(N->right);
	} 
	Node* Y = N->parent;
	while (Y != nil && N == Y->right) {
        N = Y;
        Y = Y->parent;
	}
	return Y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
	if(N->left != nil){
		return findMax(N->left);
	}
	Node* Y = N->parent;
	while (Y != nil && N == Y->left) {
        N = Y;
        Y = Y->parent;
    }
    return Y;
}

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
	Node* Y = N->right;

	N->right = Y->left;
	if (Y->left != nil){
		Y->left->parent = N;
	}

	Y->parent = N->parent;
	if(N->parent == nil){
		root = Y;
	} else if (N == N->parent->left){
		N->parent->left = Y;
	} else {
		N->parent->right = Y;
	}

	Y->left = N;
	N->parent = Y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
	Node* Y = N->left;

	N->left = Y->right;
	if (Y->right != nil){
		Y->right->parent = N;
	}

	Y->parent = N->parent;
	if(N->parent == nil){
		root = Y;
	} else if (N == N->parent->right){
		N->parent->right = Y;
	} else {
		N->parent->left = Y;
	}

	Y->right = N;
	N->parent = Y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
	Node* Y;
	while(N->parent->color == RED){
		if (N->parent == N->parent->parent->left){
			Y = N->parent->parent->right;
			if (Y->color == RED){
				N->parent->color = BLACK;
				Y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			} else {
				if (N == N->parent->right){
					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				RightRotate(N->parent->parent);
			}
		} else {
			Y = N->parent->parent->left;
			if (Y->color == RED){
				N->parent->color = BLACK;
				Y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			} else {
				if (N == N->parent->left){
					N = N->parent;
					RightRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				LeftRotate(N->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
	if (u->parent == nil){
		root = v;
	} else if (u == u->parent->left){
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
	Node* W;
	while (N != root && N->color == BLACK){
		if (N == N->parent->left){
			W = N->parent->right;
			if (W->color == RED){
				W->color = BLACK;
				N->parent->color = RED;
				LeftRotate(N->parent);
				W = N->parent->right;
			}
			if (W->left->color == BLACK && W->right->color == BLACK){
				W->color = RED;
				N = N->parent;
			} else {
				if (W->right->color == BLACK){
					W->left->color = BLACK;
					W->color = RED;
					RightRotate(W);
					W = N->parent->right;
				}
				W->color = N->parent->color;
				N->parent->color = BLACK;
				W->right->color = BLACK;
				LeftRotate(N->parent);
				N = root;
			}
		} else {
			W = N->parent->left;
			if (W->color == RED){
				W->color = BLACK;
				N->parent->color = RED;
				RightRotate(N->parent);
				W = N->parent->left;
			}
			if (W->right->color == BLACK && W->left->color == BLACK){
				W->color = RED;
				N = N->parent;
			} else {
				if (W->left->color == BLACK){
					W->right->color = BLACK;
					W->color = RED;
					LeftRotate(W);
					W = N->parent->left;
				}
				W->color = N->parent->color;
				N->parent->color = BLACK;
				W->left->color = BLACK;
				RightRotate(N->parent);
				N = root;
			}
		}
	}
	N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
	Node* Y = N;
	Node* X;
	int origCol = Y->color;
	if (N->left == nil){
		X = N->right;
		RB_Transplant(N, N->right);
	} else if (N->right == nil){
		X = N->left;
		RB_Transplant(N, N->left);
	} else {
		Y = findMin(N->right);
		origCol = Y->color;
		X = Y->right;
		if (Y->parent == N){
			X->parent = Y;
		} else {
			RB_Transplant(Y, Y->right);
			Y->right = N->right;
			Y->right->parent = Y;
		}
		RB_Transplant(N, Y);
		Y->left = N->left;
		Y->left->parent = Y;
		Y->color = N->color;
	}
	if (origCol == BLACK){
		RB_DeleteFixUp(X);
	}
	delete N;
}

// Class Constructors & Destructors ----------------------------------------

//private
Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	color = RED;
	parent = left = right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
	nil = new Node("\0", -1);
	nil->color = BLACK;
	root = nil; 
	current = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("\0", -1);
	nil->color = BLACK;
	root = current = nil; 
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
	clear();
	delete nil; 
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
	return (search(root, k) != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
	if(!contains(k)){
		throw logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
	}
	Node *N = search(root, k);
	return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
	return !(current == nil || current == nullptr);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
	if(!hasCurrent()){
		throw logic_error("Dictionary: currentKey(): current undefined");
	}
	return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
	if(!hasCurrent()){
		throw logic_error("Dictionary: currentVal(): current undefined");
	}
	return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
	postOrderDelete(root);
	root = nil; 
	current = nil;
	num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
	Node* S = search(root, k);
	if (S == nil){
		Node* X = root;
		Node* Y = nil;
		Node* N = new Node(k, v);
		N->right = N->left = nil;
		N->color = RED;

		while(X != nil){
			Y = X;
			if (k < X->key){
				X = X->left;
			} else {
				X = X->right;
			}
		}
		N->parent = Y;
		if(Y == nil){
			root = N;
			num_pairs++;
		} else if (k < Y->key){
			Y->left = N;
			num_pairs++;
		} else if (k > Y->key){
			Y->right = N;
			num_pairs++;
		} 
		RB_InsertFixUp(N);
	} else {
		S->val = v;
	}
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
	if(!contains(k)){
		throw logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
	}
	Node* N = search(root, k);
	// Node* test = findMin(N);
	// cout << "what is min " << test->key << endl;
	if (N == current){
		current = nil;
	}
	RB_Delete(N);
	num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
	if (size() > 0){
		current = findMin(root);
	}
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
	if (size() > 0){
		current = findMax(root);
	}
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
	if(!hasCurrent()){
		throw logic_error("Dictionary: next(): current undefined");
	}
	if (findNext(current) != nil) {
		Node* N = findNext(current);
		current = N;
	} else {
		current = nil;
	}
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
	if(!hasCurrent()){
		throw logic_error("Dictionary: prev(): current undefined");
	}
	if (findPrev(current) != nil) {
		Node* N = findPrev(current);
		current = N;
	} else {
		current = nil;
	}
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
	string S = "";
	this->inOrderString(S, this->root);
	return S;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
	string S = "";
	this->preOrderString(S, this->root);
	return S;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
	if(this->num_pairs != D.num_pairs){
		return false;
	}
	string A, B;
	A = this->to_string();
	B = D.to_string();
	return (A == B);
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
	return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
	if (this != &D){
		Dictionary T = D;
		swap(nil, T.nil);
		swap(root, T.root);
		swap(current, T.current);
		swap(num_pairs, T.num_pairs);
	}
	return *this;
}