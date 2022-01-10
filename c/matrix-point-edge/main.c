#include "graph.h"

void print_list(List l)
{
    for (int i = 0; i < l.size; i++)
        printf("%d\n", l.data[i]);
}

int main()
{
    freopen("./dt.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);

    Graph g;
    init_graph(&g, n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&g, g.m + 1, u, v);
    }

    printf("%d %d", max_deg(g), deg(&g, max_deg(g)));

    return 0;
}