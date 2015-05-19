#include <stdlib.h>
#include "Stack.h"
#include <stdio.h>
#include <string.h>

typedef char * stackElementT;

struct stack {
    struct stack *next; 
    stackElementT element;
};

int createS (Stack *stk){
    Stack head = (Stack)malloc(sizeof(struct stack));
    if(head == NULL){
        return false;
    }
    char * top = "top";
    head -> element = top;
    head -> next = NULL;
    *stk = head;
    return true;
}

int isEmptyS (Stack *stk){
    if( (* stk) -> next == NULL){
        return true;
    }
    return false;
}

int pushS (Stack *stk, char *s){
    Stack new = (Stack)malloc(sizeof(struct stack));
    if(new == NULL){
        return false; 
    }
    new -> element = s;
    new -> next = (* stk) -> next;
    (* stk) -> next = new;
    return true;
}

int popS (Stack *stk, char **s){
    
    if(isEmptyS(stk)){
        return false;
    }
    Stack oldnext;
    oldnext = (* stk) -> next;
    Stack newnext;
    newnext = (* oldnext).next;
    (* stk) -> next = newnext;
    (* s) = (* oldnext).element;
    free(oldnext);
    return true;
}

int topS (Stack *stk, char **s){
    if(isEmptyS(stk)){
        return false;
    }
    Stack nextnode = (* stk) -> next;
    (* s) = nextnode -> element;
    return true;
}

int destroyS (Stack *stk){
    if (*stk == NULL){
        return false;
    }
    Stack current = *stk;
    Stack nextnode;
    Stack after_next;
    while (current -> next != NULL){
        nextnode = current -> next;
        after_next = nextnode -> next;
        free(nextnode);
        current -> next = after_next;
    }
    free(current);
    *stk = NULL;
    return true;
}
