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
	//split the deck
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
	//clear the original deck and put the 2 split deck together
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

    //read max decksize
    int max = atoi(argv[1]);
    List L, J;

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    int shufCount = 0;
    int deckSize = 0;
    int i = 0;

    //perform perfect shuffle for respective deck size
    while(deckSize < max){
    	shufCount = i = 0;
    	while(i < (deckSize + 1)){
    		L.insertBefore(i);
    		J.insertBefore(i);
    		i++;
    	}
    	shuffle(L);
    	shufCount++;
    	while(!(L == J)){ //shuffle until perfect shuffle
    		shuffle(L);
    		shufCount++;
    	}
    	cout << " " << deckSize + 1 << "		" << shufCount << endl;
    	L.clear();
    	J.clear();
    	deckSize++;
    }
    return 0;
}