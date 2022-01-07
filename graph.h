#include <stack>
#include <list>
#include <queue>

#include <iostream>

using namespace std;

class graph
{
private:
    static const int max_vertices = 100;
    int m[max_vertices][max_vertices];
    int n;
    bool directed;
    void init(int n);
    void init_marked(bool arr[]);

public:
    graph(int n, bool directed);
    graph(char *filename, bool directed);
    void add_egde(int x, int y);
    void print();
    list<int> neighbors(int x);
    void dfs(int x);
    void bfs(int x);
};

void graph::init(int n)
{
    directed = false;
    this->n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            m[i][j] = 0;
}

void graph::init_marked(bool arr[])
{
    for (int i = 1; i <= max_vertices; i++)
        arr[i] = false;
}

graph::graph(int n, bool directed = false)
{
    init(n);
    this->directed = directed;
}

graph::graph(char *filename, bool directed = false)
{
    FILE *f = fopen(filename, "r");
    int n, m;

    fscanf(f, "%d%d", &n, &m);
    init(n);
    this->directed = directed;

    for (int i = 1; i <= m; i++)
    {
        int x, y;
        fscanf(f, "%d%d", &x, &y);
        add_egde(x, y);
    }

    fclose(f);
}

void graph::add_egde(int x, int y)
{
    if (x > n || y > n)
    {
        cout << "Can't add edge(" << x << ", " << y << ")" << endl;
        return;
    }
    m[x][y]++;
    if (!directed)
        m[y][x]++;
}

void graph::print()
{
    for (int i = 1; i <= n; i++)
    {
        cout << i << " -> { ";
        for (int j = 1; j <= n; j++)
            if (m[i][j])
                cout << j << " ";
        cout << "}" << endl;
    }
}

list<int> graph::neighbors(int x)
{
    list<int> l;
    for (int i = 1; i <= n; i++)
        if (m[x][i])
            l.push_back(i);
    return l;
}

void graph::dfs(int x)
{
    cout << "dfs: ";
    bool marked[max_vertices];
    init_marked(marked);
    stack<int> s;
    s.push(x);

    while (!s.empty())
    {
        int u = s.top();
        s.pop();

        if (marked[u])
            continue;

        marked[u] = true;
        if (u != x)
            cout << " -> ";
        cout << u;

        list<int> neis = neighbors(u);
        while (!neis.empty())
        {
            s.push(neis.front());
            neis.pop_front();
        }
    }
    cout << endl;
}

void graph::bfs(int x)
{
    cout << "bfs: ";
    bool marked[max_vertices];
    init_marked(marked);
    list<int> q;
    q.push_back(x);

    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();

        if (marked[u])
            continue;

        marked[u] = true;
        if (u != x)
            cout << " -> ";
        cout << u;

        list<int> neis = neighbors(u);
        while (!neis.empty())
        {
            q.push_back(neis.front());
            neis.pop_front();
        }
    }
    cout << endl;
}
