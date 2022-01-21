#include <vector>
#include <stdarg.h>

#include "edge.h"

namespace graphtheory
{
    using namespace std;

    template <typename type>
    class graph
    {
    private:
        int n;
        bool directed;
        vector<edge<type>> edges;

    public:
        graph(int n, bool directed);
        void add_edge(edge<type> e);
        void add_edge(type u, type v);
        void print_edge(int index);
        void print_edges();
    };

    // Initial graph
    template <typename type>
    graph<type>::graph(int n, bool directed)
    {
        this->n = n;
        this->directed = directed;
    }

    // Add edge
    template <typename type>
    void graph<type>::add_edge(edge<type> e)
    {
        edges.push_back(e);
        if (directed)
            return;

        edge<type> e1(e.get_v(), e.get_u());
        edges.push_back(e1);
    }

    // Add edge
    template <typename type>
    void graph<type>::add_edge(type u, type v)
    {
        edge<type> e(u, v);
        add_edge(e);
    }

    // print edge at index
    template <typename type>
    void graph<type>::print_edge(int index)
    {
        if (index >= edges.size())
            return;
        edges[index].print();
    }

    // print edges
    template <typename type>
    void graph<type>::print_edges()
    {
        for (int i = 0; i < edges.size(); i++)
        {
            print_edge(i);
            cout << endl;
        }
    }

}