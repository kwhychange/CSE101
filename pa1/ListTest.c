/*
Ko-Wei Chang
kochang
pa1
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }

   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){//
      printf("%d ", get(B));
   } 
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
    
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   moveFront(B);
   set(B, 0);
   printf("%d\n", get(B)); //set cursor data to 0
   printf("%d\n", front(B));
   printList(stdout, B);
   printf("\n");

   deleteFront(B);
   deleteBack(B);
   printList(stdout, B);
   printf("\n");

   moveFront(B);
   insertBefore(B, 20);
   moveBack(B);
   insertAfter(B, 1);
   printList(stdout, B);
   printf("\n");
   
   moveFront(B);
   for(i=0; i<10; i++) moveNext(B);
   delete(B);
   printList(stdout, B);
   printf("\n");

   printf("%d\n", front(B));
   printf("%d\n", back(B));

   moveBack(B);
   set(B, 0);
   printf("%d\n", back(B));   

   append(A, 1);
   moveFront(A);
   delete(A);
   printf("%d\n", index(A));
   printList(stdout, A);
   printf("\n");

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
0
0
0 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
20 19 18 17 16 15 14 13 12 11 9 8 7 6 5 4 3 2 1
20
1
0
-1

*/
