#include "graph.h"

int main()
{
    graphtheory::graph<int> g(10, true);
    graphtheory::edge<int> e(10, 6);
    g.add_edge(e);
    g.add_edge(e);
    g.add_edge(e);
    g.add_edge(e);
    return 0;
}