#ifndef _STACK_H
#define _STACK_H

typedef struct node* stack;
struct node{
    int val;
    stack next;
};

/*
@requires: nothing
@assigns: nothing
@ensures: Retourne une pile vide
*/
stack initStack();

/*
@requires: nothing
@assigns: stack
@ensures: ajoute newvalue sur le dessus de la pile
*/
void push(stack* s, int newValue);

/*
@requires: stack non vide
@assigns: stack
@ensures: Supprime et retourne l'élément au sommet de la pile
*/
int pop(stack *s);

/*
@requires: stack non cyclique
@assigns: nothing
@ensures: Affiche la pile
*/
void printStack(stack s);

#endif
