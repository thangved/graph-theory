#include "graph.h"

#include <stdio.h>

int main()
{
    Graph g;
    FILE *f = freopen("./dt.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&g, n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&g, u, v);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("neighbours(%d) = ", i);
        print_list(neighbours(&g, i));
    }
    fclose(f);

    return 0;
}