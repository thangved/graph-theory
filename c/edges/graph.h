#include "list.h"

#define max_edges 100

typedef struct
{
    int u, v;
} Edge;

typedef struct
{
    int n, m;
    Edge edges[max_edges];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int u, int v)
{
    if (u < 1 || v < 1 || u > pG->n || v > pG->n)
        return;
    Edge edge = {u, v};
    pG->edges[pG->m] = edge;
    pG->m++;
}

int degree(Graph *pG, int u)
{
    int deg = 0;
    for (int i = 0; i < pG->m; i++)
        deg += (pG->edges[i].u == u) + (pG->edges[i].v == u);

    return deg;
}

void sort(List *l)
{
    for (int i = 0; i < l->size; i++)
        for (int j = i + 1; j < l->size; j++)
            if (l->elements[i] > l->elements[j])
            {
                int t = l->elements[i];
                l->elements[i] = l->elements[j];
                l->elements[j] = t;
            }
}

List neighbours(Graph *pG, int u)
{
    List l;
    makenull_list(&l);
    for (int i = 0; i < pG->m; i++)
    {
        if (pG->edges[i].u == u)
            push_back(&l, pG->edges[i].v);
    }
    sort(&l);
    return l;
}
