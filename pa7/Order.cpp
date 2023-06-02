/*
Ko-Wei Chang
kochang
pa7
*/

#include "Dictionary.h"
#include <iostream>
#include<string>
#include<stdexcept>
#include<fstream>

using namespace std;

int main(int argc, char* argv[]){
	fstream infile, outfile;
	if(argc != 3){
		cerr << "Usage: ./Order <input file> <output file>" << endl;
    	exit(EXIT_FAILURE);
    }

    //open
    infile.open(argv[1], ios::in);
    outfile.open(argv[2], ios::out);
    if (!infile.is_open()){
    	cerr << "Unable to open input file:" << argv[1] << endl;
    	exit(EXIT_FAILURE);
    }
    if (!outfile.is_open()){
    	cerr << "Unable to open output file:" << argv[2] << endl;
    	exit(EXIT_FAILURE);
    }

    //read
    Dictionary D;
    string s = "";
    int i = 1;
    while(getline(infile, s)){
    	D.setValue(s, i);
    	i++;
    }

    outfile << D.to_string() << endl;
    outfile << D.pre_string() << endl;

    D.clear();

    //close file
    infile.close();
    outfile.close();

    return 0;
}