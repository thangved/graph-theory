#include "graph.h"

int main()
{
    FILE *f = freopen("./dt1.txt", "r", stdin);

    int n, m;
    scanf("%d%d", &n, &m);
    Graph g;
    init_graph(&g, n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&g, u, v);
    }

    print_graph(g);

    fclose(f);

    return 0;
}