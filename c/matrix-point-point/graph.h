#include "list.h"
#define MAX_N 100

typedef struct
{
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->m = 0;
    pG->n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int u, int v)
{
    pG->A[u][v] = 1;
    pG->A[v][u] = 1;
    pG->m++;
}

int degree(Graph *pG, int u)
{
    int d = 0;
    for (int i = 1; i <= pG->n; i++)
        d += i != u ? pG->A[u][i] : 2 * pG->A[u][i];
    return d;
}

int deg(Graph *pG, int u)
{
    int d = 0;
    for (int i = 1; i <= pG->n; i++)
        d += pG->A[u][i];
    return d;
}

int indegree(Graph *pG, int u)
{
    int d = 0;
    for (int i = 1; i <= pG->n; i++)
        d += pG->A[i][u];
    return d;
}

int outdegree(Graph *pG, int u)
{
    int d = 0;
    for (int i = 1; i <= pG->n; i++)
        d += pG->A[u][i];
    return d;
}

List neighbours(Graph g, int u)
{
    List l;
    makenull_list(&l);
    for (int i = 1; i <= g.n; i++)
        if (g.A[u][i])
            for (int c = 0; c < g.A[u][i]; c++)
                push_back(&l, i);

    return l;
}

void print_edges(Graph g)
{
    for (int i = 1; i <= g.n; i++)
        for (int j = 1; j <= g.n; j++)
            if (g.A[i][j])
                for (int c = 1; c <= g.A[i][j]; c++)
                    printf("%d %d\n", i, j);
}

void print_graph(Graph g)
{
    for (int i = 1; i <= g.n; i++)
    {
        for (int j = 1; j <= g.n; j++)
            printf("%d ", g.A[i][j]);
        printf("\n");
    }
}

void print_max_deg(Graph g)
{
    int u = 1, max = 0;
    for (int i = 1; i <= g.n; i++)
        if (deg(&g, i) > max)
        {
            max = deg(&g, i);
            u = i;
        }
    printf("%d %d", u, max);
}
