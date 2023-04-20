/*
Ko-Wei Chang
kochang
pa2
*/

#include "List.h"

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
    int length;
    int index;
    Node cursor;
    Node front;
    Node back;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
Node newNode(int x){
    Node N = malloc(sizeof(NodeObj));
    N->data = x;
    N->prev = N->next = NULL;
    return(N);
}

void freeNode(Node* pN){
    if ( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}

List newList(void){
    List L; 
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
} // Creates and returns a new empty List.

void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL){
        while (length(*pL) != 0){
            deleteFront(*pL);
        }
        free(*pL);
        *pL=NULL;
    }
} // Frees all heap memory associated with *pL, and sets
 // *pL to NULL.

// Access functions -----------------------------------------------------------
int length(List L){
    if (L==NULL){
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
} // Returns the number of elements in L.

int index(List L){
    if(L==NULL){
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
} // Returns index of cursor element if defined, -1 otherwise.

int front(List L){
    if(L==NULL){
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L)==0){
        printf("List Error: calling front() on an empty List\n");
    }
    return(L->front->data);
} // Returns front element of L. Pre: length()>0

int back(List L){
    if(L==NULL){
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L)==0){
        printf("List Error: calling back() on an empty List\n");
    }
    return(L->back->data);
} // Returns back element of L. Pre: length()>0

int get(List L){
    if(L==NULL){
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L)==0){
        printf("List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL || index(L) < 0){
        printf("List Error: calling get() on an undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    return(L->cursor->data);
} // Returns cursor element of L. Pre: length()>0, index()>=0

bool equals(List A, List B){
    if( A==NULL || B==NULL ){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    bool eq;
    Node N, M;

    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;
    while( eq && N!=NULL){
       eq = ( N->data==M->data );
       N = N->next;
       M = M->next;
    }
   return eq;
} // Returns true iff Lists A and B are in same
 // state, and returns false otherwise.

// Manipulation procedures ----------------------------------------------------
void clear(List L){
    if(L==NULL){
        printf("List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    while (length(L) != 0){
        deleteFront(L);
    }
    L->index = -1;
    L->cursor = NULL;
} // Resets L to its original empty state.

void set(List L, int x){
    if(L==NULL){
        printf("List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L)>0 && index(L)>=0 && L->cursor != NULL){
        L->cursor->data = x;
    }
} // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0

void moveFront(List L){
    if(L==NULL){
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L)>0){
        L->cursor = L->front;
        L->index = 0;
    }
} // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.

void moveBack(List L){
    if(L==NULL){
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L)>0){
        L->cursor = L->back;
        L->index = L->length - 1;
    }
} // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.

void movePrev(List L){
    if(L==NULL){
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL){
        if(L->cursor != L->front){
            L->cursor = L->cursor->prev;
            L->index--;
        } else {
            L->cursor = NULL;
            L->index = -1;            
        }
    }
} // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing

void moveNext(List L){
    if(L==NULL){
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL){
        L->cursor = L->cursor->next;
        if(L->cursor != NULL){
            L->index++;
        } else {
            L->index = -1;
        }
    }
} // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing

void prepend(List L, int x){
    Node N = newNode(x);

    if(L==NULL){
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0){
        L->front = L->back = N; 
    }else{ 
        N->next = L->front;
        L->front->prev = N; 
        L->front = N; 
        if(L->cursor != NULL){
            L->index++;
        }
    }

    L->length++;
} // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.

void append(List L, int x){
    Node N = newNode(x);

    if(L==NULL){
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0){
        L->front = L->back = N; 
    }else{ 
        N->prev = L->back;
        L->back->next = N;
        L->back = N; 
    }
    L->length++;
} // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.

void insertBefore(List L, int x){
    Node N = newNode(x);
    if(L==NULL){
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == NULL || index(L)<0){
        printf("List Error: calling insertBefore() on NULL cursor reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L)>0 && L->cursor == L->front){
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    } else {
        N->prev = L->cursor->prev;
        N->next = L->cursor;
        L->cursor->prev = N;
        N->prev->next = N;
    }
    L->index++;
    L->length++;
} // Insert new element before cursor.
 // Pre: length()>0, index()>=0

void insertAfter(List L, int x){
    Node N = newNode(x);
    if(L==NULL){
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == NULL || index(L)<0){
        printf("List Error: calling insertAfter() on NULL cursor reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L)>0 && L->cursor == L->back){
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    } else {
        N->next = L->cursor->next;
        N->prev = L->cursor;
        L->cursor->next = N;
        N->next->prev = N;
    }
    L->length++;
} // Insert new element after cursor.
 // Pre: length()>0, index()>=0

void deleteFront(List L){
    Node N = NULL;
    if(L==NULL){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    N = L->front;
    if(length(L)>1){
        if (L->cursor == N){
            L->cursor = NULL;
        }
        L->front = L->front->next;
        L->front->prev = NULL;
        L->index--;
    } else {
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
    }
    L->length--;
    freeNode(&N);
} // Delete the front element. Pre: length()>0

void deleteBack(List L){
    Node N = NULL;
    if(L==NULL){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    N = L->back;
    if(length(L)>1){
        if (L->cursor == N){
            L->cursor = NULL;
            L->index = -1;
        }
        L->back = L->back->prev;
        L->back->next = NULL;
    } else {
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
    }
    L->length--;
    freeNode(&N);
} // Delete the back element. Pre: length()>0

void delete(List L){
    Node N = NULL;
    if(L==NULL){
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL || index(L)<0){
        printf("List Error: calling delete() on NULL cursor reference\n");
        exit(EXIT_FAILURE);
    }
    N = L->cursor;
    L->cursor = NULL;
    if (length(L)==1){
        L->front = L->back = NULL;
    } else if(N == L->front){
        deleteFront(L);
    } else if(N == L->back){
        deleteBack(L);
    } else {
        N->prev->next = N->next;
        N->next->prev = N->prev;
    }
    freeNode(&N);
    L->length--;
    L->index = -1;
} // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
    Node N = NULL;

    if( L==NULL ){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, "%d ", N->data);
    }
} // Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.

List copyList(List L){
    if( L==NULL ){
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List nL = newList(); 
    Node N = L->front;
    while (N != NULL) {
        append(nL, N->data);
        N = N->next;
    }
    return(nL);
} // Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.