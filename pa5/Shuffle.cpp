/*
Ko-Wei Chang
kochang
pa5
*/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D){
	List A, B;
	D.moveFront();
	for (int i = 0; i < D.length() / 2; ++i)
	{
		A.insertBefore(D.peekNext());
		D.moveNext();
	}
	for (int j = D.length() / 2; j < D.length(); ++j)
	{
		B.insertBefore(D.peekNext());
		D.moveNext();
	}
	D.clear();
	A.moveFront();
	B.moveFront();
	while(A.position() != A.length() || B.position() != B.length()){
		if(B.position() != B.length()){
			D.insertBefore(B.peekNext());
			B.moveNext();
		}
		if(A.position() != A.length()){
			D.insertBefore(A.peekNext());
			A.moveNext();
		}
	}
}

int main(int argc, char* argv[]){
	if(argc != 2){
		cout << "Usage: Shuffle.cpp <number>" << endl;
    	exit(EXIT_FAILURE);
    }

    //read int
    int decksize = atoi(argv[1]);
    List L, J;

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    int s = 0;
    int i = 0, k;

    while(i < decksize){
    	s = k = 0;
    	while(k < (i + 1)){
    		L.insertBefore(k);
    		J.insertBefore(k);
    		k++;
    	}
    	shuffle(L);
    	s++;
    	while(!(L == J)){
    		shuffle(L);
    		s++;
    	}
    	cout << " " << i + 1 << "		" << s << endl;
    	L.clear();
    	J.clear();
    	i++;
    }
    return 0;
}