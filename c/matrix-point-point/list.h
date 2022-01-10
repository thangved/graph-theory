#include <stdio.h>

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