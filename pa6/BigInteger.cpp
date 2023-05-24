/*
Ko-Wei Chang
kochang
pa6
*/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
#include"List.h"

const int POWER = 9;
const long BASE = 1000000000;

using namespace std;

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
	signum = 0;    // +1 (positive), -1 (negative), 0 (zero)
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
	if (x > 0) {
		signum = 1;
	} else {
		signum = -1;
	}
	long i = x % BASE;
	while(i > 0){
		digits.insertAfter(i);
		x = x / BASE;
		i = x % BASE;
	}
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	if(s.length() == 0){
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	if (s[0] == '+'){
		signum = 1; 
		s.substr(1, s.length());
	}
	if (s[0] == '-'){
		signum = -1;
		s.substr(1, s.length());
	} else {
		signum = 1;
	}
	
	for (char c : s){
		if (!isdigit(c) && c != '-' && c != '+'){
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
	}
	int i = s.length() - POWER;
	while(i > 0)
	{
		digits.insertAfter(stol(s.substr(i, POWER)));
		i -= POWER;
	}
	if (i < 0) {
		if (s[0] == '+' || s[0] == '-') {
			digits.insertAfter(stol(s.substr(1, i + POWER -1)));
		} else {
			digits.insertAfter(stol(s.substr(0, i + POWER)));
		}
	} else if (i == 0){
		digits.insertAfter(stol(s.substr(i, POWER)));
	}
	digits.moveFront();
	while(digits.peekNext() == 0 && digits.length() > 1){
		digits.eraseAfter();
	}
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
	this->signum = N.signum; 
	this->digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
	return this->signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	if (this->signum < N.signum){
		return -1;
	} else if (this->signum > N.signum){
		return 1;
	} else if (this->signum == 0 && 0 == N.signum){
		return 0;
	}

	List A = this->digits;
	List B = N.digits;
	if (this->signum == N.signum){
		if(this->signum == 1){
			if(A.length() > B.length()){
				return 1;
			} else if (A.length() < B.length()){
				return -1;
			} 
			A.moveFront();
			B.moveFront();
			while(A.position() < A.length())
			{
				if(A.peekNext() > B.peekNext()){
					return 1;
				} else if (A.peekNext() < B.peekNext()){
					return -1;
				}
				A.moveNext();
				B.moveNext();
			}
			return 0;
		}
		if(this->signum == -1){
			if(A.length() > B.length()){
				return -1;
			} else if (A.length() < B.length()){
				return 1;
			} 
			A.moveFront();
			B.moveFront();
			while(A.position() < A.length())
			{
				if(A.peekNext() > B.peekNext()){
					return -1;
				} else if (A.peekNext() < B.peekNext()){
					return 1;
				}
				A.moveNext();
				B.moveNext();
			}
			return 0;
		}
	}
	return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	signum = 0;
	digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
	signum *= -1;
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
	L.moveFront();
	while(L.position() < L.length()){
		L.setAfter(L.peekNext() * m);
		L.moveNext();
	}
}

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
	scalarMultList(L, -1);
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
	S.clear();
	scalarMultList(B, sgn);

	A.moveBack();
    B.moveBack();
    while (A.position() > 0 && B.position() > 0) {
        S.insertAfter(A.peekPrev() + B.peekPrev());
        A.movePrev();
        B.movePrev();
    }
    while (A.position() > 0) {
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }
    while (B.position() > 0) {
        S.insertAfter(B.peekPrev());
        B.movePrev();
    }
    S.moveFront();
	while(S.peekNext() == 0 && S.length() > 1){
		S.eraseAfter();
	}
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
	int sign = 1;
	if(L.peekNext() == 0){
		return 0;
	}
	if (L.peekNext() < 0){
		negateList(L);
		sign = -1;
	}
	long val = 0;
	long carry = 0;
	L.moveBack();
	while(L.position() > 0){
		val = L.peekPrev();
		if (val < 0){
			val += BASE + carry;
			L.setBefore(val);
			carry = -1;
		} else {
			val += carry;
			carry = 0;
			if (val >= BASE){
				carry = val/BASE;
				val = val % BASE;
			}
			L.setBefore(val);
		}
		L.movePrev();
	}
	if(carry != 0){
		L.moveFront();
		L.insertAfter(carry);
	}
	return sign;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
	L.moveBack();
	for (int i = 0; i < p; ++i)
	{
		L.insertAfter(0);
	}
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	BigInteger M;
	List A = this->digits;
	List B = N.digits;
	List sum;
	if(this->signum == -1){
		negateList(A);
	}
	if(N.signum == -1){
		negateList(B);
	}
	sumList(sum, A, B, 1);
	// cout << sum << endl;
	M.signum = normalizeList(sum);
	M.digits = sum;
	return M;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
	BigInteger M;
	BigInteger negN = N;
	negateList(negN.digits);
	M = this->add(negN);
	return M;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
	BigInteger M;
	if(this->signum == 0 || N.signum == 0){
		return M;
	}
	List prod;
	List A;
	List B = N.digits;
	int shift = 0;
	prod.insertAfter(0);
	B.moveBack();
	while(B.position() > 0){
		A = this->digits;
		scalarMultList(A, B.peekPrev());
		shiftList(A, shift);
		List temp = prod;
		sumList(prod, temp, A, 1);
		normalizeList(prod);
		B.movePrev();
		shift++;
	}
	M.digits = prod;
	M.signum = this->signum * N.signum;
	return M;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
	string s = "";
	if (this->signum == 0){
		return "0";
	} else if (signum == -1){
		s += "-";
	}
	digits.moveFront();
	while(digits.peekNext() == 0 && digits.length() > 1){
		digits.moveNext();
	}
	while(digits.position() != digits.length()){
		string temp = std::to_string(digits.peekNext());
		string zeros = "";
		while((zeros.length() + temp.length()) < POWER && digits.position() != 0){
			zeros += "0";
		}
		s += (zeros + temp);
		digits.moveNext();
	}
	return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) == 0);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) == -1);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) <= 0);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) == 1);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) >= 0);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	A = A.BigInteger::add(B);
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	A = A.BigInteger::sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	A = A.BigInteger::mult(B);
	return A;
}