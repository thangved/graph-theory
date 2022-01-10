#include "list.h"
#include <stdio.h>

typedef struct
{
    int A[100][500];
    int n, m;
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < 500; j++)
            pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int e, int x, int y)
{
    pG->A[x][e]++;
    pG->A[y][e]++;
    pG->m++;
}

void print_graph(Graph g)
{
    for (int i = 1; i <= g.m; i++)
    {
        for (int j = 1; j <= g.n; j++)
            printf("%s ", g.A[j][i] ? "x" : "-");
        printf("\n");
    }
}

List neighbours(Graph *pG, int u)
{
    List l;
    make_null(&l);
    for (int col = 0; col < pG->m; col++)
        if (pG->A[u][col])
        {
            int added = 0;
            for (int row = 1; row <= pG->n; row++)
                if (pG->A[row][col] && u != row)
                {
                    push_back(&l, row);
                    added = 1;
                }
            if (!added)
                push_back(&l, u);
        }
    return l;
}

int deg(Graph *pG, int x)
{
    int d = 0;
    for (int col = 1; col <= pG->m; col++)
        d += pG->A[x][col];
    return d;
}

int max_deg(Graph g)
{
    int u = 1, max = 0;
    for (int i = 1; i <= g.n; i++)
        if (deg(&g, i) > max)
        {
            max = deg(&g, i);
            u = i;
        }
    return u;
}
