#include "graph.h"

int main()
{
    freopen("./dt1.txt", "r", stdin);

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

    printf("%d", count_connected(&g));

    return 0;
}