#include "graph.h"

int main()
{
    // with un-directed
    cout << "with un-directed" << endl;
    graph g1((char *)"./graph.txt");
    g1.print();
    g1.dfs(1);
    g1.bfs(1);

    // with directed
    cout << "with directed" << endl;
    graph g2((char *)"./graph.txt", true);
    g2.print();
    g2.dfs(1);
    g2.bfs(1);

    cout << g2.degree(2);

    return 0;
}