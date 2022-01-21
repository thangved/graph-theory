#include <iostream>

namespace graphtheory
{
    using namespace std;
    template <typename type>
    class edge
    {
    private:
        type u, v;

    public:
        edge(type u, type v);
        type get_u();
        type get_v();
        void print();
        void println();
    };

    // Initial method
    template <typename type>
    edge<type>::edge(type u, type v)
    {
        this->u = u;
        this->v = v;
    }

    // get u value
    template <typename type>
    type edge<type>::get_u()
    {
        return u;
    }

    // get v value
    template <typename type>
    type edge<type>::get_v()
    {
        return v;
    }

    // print edge
    template <typename type>
    void edge<type>::print()
    {
        cout << (type)u << " -> " << (type)v;
    }

    // print edge with new line
    template <typename type>
    void edge<type>::println()
    {
        print();
        cout << endl;
    }
}