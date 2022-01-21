#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int elements[100];
    int size;
} List;

void makenull_list(List *pL)
{
    pL->size = 0;
}

int empty(List l)
{
    return !l.size;
}

int front(List l)
{
    return l.elements[0];
}
int member(int x, List l)
{
    for (int i = 0; i < l.size; i++)
        if (l.elements[i] == x)
            return 1;
    return 0;
}
void push_back(List *pL, int x)
{
    pL->elements[pL->size] = x;
    pL->size++;
}

void pop_front(List *pL)
{
    for (int i = 0; i < pL->size; i++)
        pL->elements[i] = pL->elements[i + 1];
    pL->size--;
}
void print_list(List l)
{
    for (int i = 0; i < l.size; i++)
        printf("%d ", l.elements[i]);
}

void pop_back(List *pL)
{
    if (empty(*pL))
        return;
    pL->size--;
}

int back(List l)
{
    return l.elements[l.size - 1];
}

// Stack
typedef List Stack;
void pop_stack(Stack *pStack)
{
    pop_back(pStack);
}

int empty_stack(Stack s)
{
    return empty(s);
}

int top(Stack s)
{
    return back(s);
}

void push_stack(Stack *pStack, int x)
{
    push_back(pStack, x);
}
