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

void make_false(int arr[])
{
    for (int i = 0; i < 100; i++)
        arr[i] = 0;
}

void bfs(Graph *pG, int u, int marked[])
{
    List queue;
    makenull_list(&queue);
    push_back(&queue, u);
    while (!empty(queue))
    {
        u = front(queue);
        pop_front(&queue);
        if (marked[u])
            continue;
        marked[u] = 1;
        printf("%d\n", u);
        List l = neighbours(*pG, u);

        while (!empty(l))
        {
            push_back(&queue, front(l));
            pop_front(&l);
        }
    }
}

void bfs_all(Graph *pG)
{
    int marked[100];
    make_false(marked);
    for (int i = 1; i <= pG->n; i++)
        bfs(pG, i, marked);
}

void dfs(Graph *pGraph, int u, int marked[])
{
    Stack stack;
    makenull_list(&stack);
    push_stack(&stack, u);

    while (!empty_stack(stack))
    {
        u = top(stack);
        pop_stack(&stack);

        if (marked[u])
            continue;

        marked[u] = 1;
        printf("%d\n", u);

        List l = neighbours(*pGraph, u);
        while (!empty(l))
        {
            push_stack(&stack, back(l));
            pop_back(&l);
        }
    }
}

void dfs_all(Graph *pGraph)
{
    int marked[100];
    make_false(marked);

    for (int i = 1; i <= pGraph->n; i++)
        dfs(pGraph, i, marked);
}

int *parent_in_bfs(Graph *pG)
{
    int marked[100];
    int *parents = (int *)malloc(sizeof(int) * 100);
    make_false(marked);
    make_false(parents);

    List queue;
    makenull_list(&queue);

    for (int i = 1; i <= pG->n; i++)
    {
        if (marked[i])
            continue;
        push_back(&queue, i);
        parents[i] = -1;

        while (!empty(queue))
        {
            int u = front(queue);
            pop_front(&queue);
            if (marked[u])
                continue;
            marked[u] = 1;
            List l = neighbours(*pG, u);

            while (!empty(l))
            {
                if (!parents[front(l)])
                    parents[front(l)] = u;
                push_back(&queue, front(l));
                pop_front(&l);
            }
        }
    }

    return parents;
}

int *parent_in_dfs(Graph *pG)
{
    int marked[100];
    int *parents = (int *)malloc(sizeof(int) * 100);
    make_false(marked);
    make_false(parents);

    Stack stack;
    makenull_list(&stack);

    for (int i = 1; i <= pG->n; i++)
    {
        if (marked[i])
            continue;
        push_stack(&stack, i);
        parents[i] = -1;

        while (!empty(stack))
        {
            int u = top(stack);
            pop_stack(&stack);
            if (marked[u])
                continue;
            marked[u] = 1;
            List l = neighbours(*pG, u);

            while (!empty(l))
            {
                if (!marked[back(l)])
                    parents[back(l)] = u;
                push_stack(&stack, back(l));
                pop_back(&l);
            }
        }
    }

    return parents;
}

int min(int x, int y)
{
    return x < y ? x : y;
}

void check_connect(Graph *pGraph, int u, int *k, int num[], int min_num[], int on_stack[], Stack *pStack)
{
    if (num[u])
        return;

    num[u] = *k;
    min_num[u] = *k;
    *k = *k + 1;
    push_stack(pStack, u);
    on_stack[u] = 1;

    List l = neighbours(*pGraph, u);
    while (!empty(l))
    {
        int v = front(l);
        pop_front(&l);
        if (!num[v])
        {
            check_connect(pGraph, v, k, num, min_num, on_stack, pStack);
            min_num[u] = min(min_num[u], min_num[v]);
        }
        else if (on_stack[v])
            min_num[u] = min(min_num[u], num[v]);
    }

    if (num[u] == min_num[u])
    {
        while (top(*pStack) != u)
        {
            on_stack[top(*pStack)] = 0;
            pop_stack(pStack);
        }
        on_stack[top(*pStack)] = 0;
        pop_stack(pStack);
    }
}

int count_connected(Graph *pGraph)
{
    // Initial value;
    int num[100];
    int min_num[100];
    int on_stack[100];
    make_false(num);
    make_false(min_num);
    make_false(on_stack);

    Stack s;
    makenull_list(&s);

    int k = 1;

    for (int i = 1; i <= pGraph->n; i++)
        check_connect(pGraph, i, &k, num, min_num, on_stack, &s);

    int cnt = 0;
    for (int i = 1; i <= pGraph->n; i++)
        cnt += num[i] == min_num[i];
    return cnt;
}
