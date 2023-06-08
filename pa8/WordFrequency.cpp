/*
Ko-Wei Chang
kochang
pa8
*/

#include "Dictionary.h"
#include <iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]){
	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
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
    string s, key;
    size_t len, begin, end;
    while(getline(infile, s)){
    	len = s.length();

		begin = min(s.find_first_not_of(delim, 0), len);
		end = min(s.find_first_of(delim, begin), len);
		key = s.substr(begin, end-begin);

		while( key!="" ){  
			transform(key.begin(), key.end(), key.begin(), ::tolower);
			
			if(D.contains(key)){
				D.getValue(key)++;
			} else {
				D.setValue(key, 1);
			}

			begin = min(s.find_first_not_of(delim, end+1), len);
			end = min(s.find_first_of(delim, begin), len);
			key = s.substr(begin, end-begin);
		}
    }

    //print
    outfile << D << endl;
   
    //close file
    D.clear();
    infile.close();
    outfile.close();

    return 0;
}