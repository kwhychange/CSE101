/*
Ko-Wei Chang
kochang
pa8
*/

//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

	Dictionary X;
   // X.setValue("a", 1);
   //  X.setValue("b", 5);
   //  X.setValue("c", 16);
   //  X.setValue("d", 176);
   //  X.setValue("e", 3214);
   //  X.begin();
   //  X.next();
   //  X.next();

   //  if (X.currentKey() != "c" || X.currentVal() != 16){
   //    cout << "current " << X.currentKey() << " val: " << X.currentVal() << endl;
   // }
   //    X.setValue("X", 1);
   //  X.setValue("b", 5);
   //  X.setValue("e", 10);
   //  X.end();
   //  X.setValue("h", 15);
   //  X.setValue("f", 20);
   //  X.setValue("i", 100);
   //  X.end();
   //  X.prev();
   //  X.prev();
   //  cout << X;
   //  if (X.currentKey() != "f" || X.currentVal() != 20)
   //    cout << "current " << X.currentKey() << " val: " << X.currentVal() << endl;

   // cout << X;
   X.setValue("sad", 1);
   X.setValue("sadly", 2);
   X.setValue("sad", 100);
   X.setValue("sadly", 200);
   X.setValue("sadliest", 3);
   X.setValue("depression", 4);

   // cout <<X.size() << endl <<X;

   // X.remove("sad");
   // cout << endl << X.size() << endl <<X;
   // X.remove("sadly");
   // cout << endl << X.size() << endl <<X;
   // X.remove("sadliest");
   // cout << endl << X.size() << endl <<X;
   // X.remove("depression");	

	// string ideal1 = "d\nb\nc (RED)\nf\ne (RED)\ng (RED)\n";
    // string ideal2 = "e\nb\nc (RED)\nf\ng (RED)\n";
    // string ideal3 = "e\nb\nc (RED)\nf\n";
    // // string ideal2 = "c\nb\nf\ne (RED)\ng (RED)\n";
    // // string ideal3 = "c\nb\nf\ne (RED)\n";
    X.setValue("d", 1);
    X.setValue("b", 5);
    X.setValue("a", 10);
    X.setValue("c", 15);
    X.setValue("f", 20);
    X.setValue("e", 25);
    X.setValue("g", 30);
    X.begin();
	// cout <<X.pre_string() << endl;

	Dictionary Z = X;
	Dictionary Y = Z;
	cout << Z.pre_string()<<endl;
	cout << Y.pre_string()<<endl;
	cout << Z.size() << endl <<Z << endl;
	cout << Y.size() << endl <<Y << endl;


    // X.remove("a");
    
	// cout <<X.pre_string() << endl;
	// cout << X.size() << endl <<X << endl;
    // if (X.pre_string() != ideal1){
    //   cout << "interesting" << endl;
    // }
    // cout << ideal1 << endl;

 
  string S[] =   { // words to insert
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };
   string T[] =   { // words to delete
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",      
                  };

   Dictionary A;
   Dictionary B;

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+1);
   }
   
   // call operator=()
   B = A;

   B.setValue("deschooler", 101);
   B.setValue("reinsurer", 102);
   B.setValue("glagolitic", 103);
   B.setValue("cul", 104);
   B.setValue("ambusher", 105);

   // call copy constructor
   Dictionary C = B;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   // check copy constructor
   cout << "copy constructor creates identical trees: " << endl;
   cout << ((C.pre_string()==B.pre_string())?"true":"false") << endl;
   cout << endl;

   cout<<B.pre_string() << endl;
   cout<< C.pre_string() << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl;
   A.getValue("hemiolia") *= 10; // change the value associated with "hemiolia"
   cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // remove some pairs from A
   for(int i=0; i<13; i++){ 
      A.remove(T[i]);
   }

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // do forward iteration on B
   cout << "forward iteration on B, changing values:" << endl;
   for(B.begin(); B.hasCurrent(); B.next()){
      cout << "("+B.currentKey()+", " << B.currentVal() << ") ";
      B.currentVal()++;  // change value
      cout << "("+B.currentKey()+", " << B.currentVal() << ")\n";
   }
   cout << endl;

   // do reverse iteration on C
   cout << "reverse iteration on C, changing values" << endl;
   for(C.end(); C.hasCurrent(); C.prev()){
      cout << "("+C.currentKey()+", " << C.currentVal() << ") ";
      C.currentVal()++;  // change value
      cout << "("+C.currentKey()+", " << C.currentVal() << ")\n";
   }
   cout << endl;
   
   // check exceptions
   cout << "test pre-condition errors:" << endl;
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << endl;  
   

   return( EXIT_SUCCESS );
}
