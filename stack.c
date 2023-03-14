#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

stack initStack(void){
    return (NULL);
}

void push(stack* s, int newValue){
     stack newstack=malloc(sizeof(stack));
    newstack->val = newValue;
    newstack->next = *s;
    *s = newstack; 
}

int pop(stack *s){
    if(*s == NULL){
        exit(EXIT_FAILURE);
    }
    int popped = (*s)->val;
    (*s)=(*s)->next;
    return popped;
}

void printStack(stack s){
    printf("/TOP/\n");
    while(s!=NULL){
        printf("/%2d/\n", s->val);
        s=s->next;
    }
    printf("/BOTTOM/\n");
}