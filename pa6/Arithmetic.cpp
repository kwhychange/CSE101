/*
Ko-Wei Chang
kochang
pa6
*/

#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include"BigInteger.h"

using namespace std;

int main(int argc, char* argv[]){
	fstream infile, outfile;

	if(argc != 3){
		cerr << "Usage: ./Arithmetic.cpp <input file> <output file>" << endl;
    	exit(EXIT_FAILURE);
    }

    //open file
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

    //read infile
    string str1, str2;
    infile >> str1;
    infile >> str2;

    //calculate
    BigInteger A = str1;
    BigInteger B = str2;

    //print result
    //A
    outfile << A << endl << endl;
    //B
    outfile << B << endl << endl;
    //A+B
    outfile << A+B << endl << endl;
    //A-B
    outfile << A-B << endl << endl;
    //A-A
    outfile << A-A << endl << endl;
    //3A-2B
    outfile << 3*A-2*B << endl << endl;
    //AB
    outfile << A*B << endl << endl;
    //A^2
    outfile << A*A << endl << endl;
    //B^2
    outfile << B*B << endl << endl;
    //9A^4+16B^5
    outfile << 9*(A*A*A*A)+16*(B*B*B*B*B) << endl << endl;

    //close file
    infile.close();
    outfile.close();

    return 0;
}