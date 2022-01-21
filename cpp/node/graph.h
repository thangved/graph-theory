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
    void init_array(int arr[]);

public:
    graph(int n, bool directed);
    graph(char *filename, bool directed);
    void add_edge(int x, int y);
    void print();
    list<int> neighbours(int x);
    void dfs(int x);
    void bfs(int x);
    int degree(int x);
    void scc(int u, int &k, bool on_stack[], int num[], int min_num[]);
    void scc_char(int u, int &k, bool on_stack[], int num[], int min_num[]);
    int getN();
};

int graph::getN()
{
    return n;
}

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

void graph::init_array(int arr[])
{
    for (int i = 1; i <= max_vertices; i++)
        arr[i] = 0;
}

graph::graph(int n, bool directed = false)
{
    init(n);
    this->directed = directed;
}

graph::graph(char *filename, bool directed = false)
{
    FILE *f = fopen64(filename, "r");
    int n, m;

    fscanf(f, "%d%d", &n, &m);
    init(n);
    this->directed = directed;

    for (int i = 1; i <= m; i++)
    {
        int x, y;
        fscanf(f, "%d%d", &x, &y);
        add_edge(x, y);
    }

    fclose(f);
}

void graph::add_edge(int x, int y)
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

list<int> graph::neighbours(int x)
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

        list<int> neighbours_list = neighbours(u);
        while (!neighbours_list.empty())
        {
            s.push(neighbours_list.front());
            neighbours_list.pop_front();
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

        list<int> neighbours_list = neighbours(u);
        while (!neighbours_list.empty())
        {
            q.push_back(neighbours_list.front());
            neighbours_list.pop_front();
        }
    }
    cout << endl;
}

int graph::degree(int x)
{
    int d = 0;
    for (int i = 1; i <= n; i++)
        d += m[x][i];
    return d;
}

void PrintStack(stack<int> s)
{
    if (s.empty())
        return;

    int x = s.top();

    s.pop();

    PrintStack(s);
    cout << x << " ";
    s.push(x);
}

void PrintList(list<int> l)
{
    for (auto i = l.begin(); i != l.end(); i++)
        cout << *i << " ";
}

void graph::scc(int u, int &k, bool on_stack[], int num[], int min_num[])
{
    static stack<int> s;

    num[u] = k;
    min_num[u] = k;
    on_stack[u] = true;
    s.push(u);
    k++;

    cout << "---" << endl;
    cout << "SCC(" << u << ")" << endl;
    cout << "num[" << u << "] = min_num[" << u << "] = " << num[u] << endl;
    cout << "stack = [ ";
    PrintStack(s);
    cout << "]" << endl;

    list<int> neighbours_list = neighbours(u);
    cout << "neighbours(" << u << ") = [ ";
    PrintList(neighbours_list);
    cout << "]" << endl;

    while (!neighbours_list.empty())
    {
        int v = neighbours_list.front();
        neighbours_list.pop_front();
        if (!num[v])
        {
            cout << "Chua duyet" << endl;
            scc(v, k, on_stack, num, min_num);
            min_num[u] = min(min_num[u], min_num[v]);
            cout << "min_num[" << u << "] = min(min_num[" << u << "]"
                 << ", min_num[" << v << "]) = " << min(min_num[u], min_num[v]) << endl;
            ;
        }
        else if (on_stack[v])
        {
            cout << "Da duyet, con tren ngan xep" << endl;
            min_num[u] = min(min_num[u], num[v]);

            cout << "min_num[" << u << "] = min(min_num[" << u << "], num[" << v << "]) = " << min_num[u] << endl;
        }
        else
            cout << "Bo qua" << endl;
    }

    if (num[u] == min_num[u])
    {
        cout << "num[" << u << "] == min_num[" << u << "]" << endl;
        cout << "\t\t\t\t\tpops = [ ";
        while (s.top() != u)
        {
            on_stack[s.top()] = false;
            cout << s.top() << " ";
            s.pop();
        }
        on_stack[s.top()] = false;
        cout << s.top() << "]" << endl;
        s.pop();

        cout << "stack = [ ";
        PrintStack(s);
        cout << "]" << endl;
    }
    else
    {
        cout << "num[" << u << "] != min_num[" << u << "]" << endl;
    }
}

void PrintStack_char(stack<int> s)
{
    if (s.empty())
        return;

    int x = s.top();

    s.pop();

    PrintStack_char(s);
    cout << (char)(x + 'A' - 1) << " ";
    s.push(x);
}

void PrintList_char(list<int> l)
{
    for (auto i = l.begin(); i != l.end(); i++)
        cout << (char)(*i + 'A' - 1) << " ";
}

void graph::scc_char(int u, int &k, bool on_stack[], int num[], int min_num[])
{
    static stack<int> s;

    num[u] = k;
    min_num[u] = k;
    on_stack[u] = true;
    s.push(u);
    k++;

    cout << "---" << endl;
    cout << "SCC(" << (char)(u + 'A' - 1) << ")" << endl;
    cout << "num[" << (char)(u + 'A' - 1) << "] = min_num[" << (char)(u + 'A' - 1) << "] = " << num[u] << endl;
    cout << "stack = [ ";
    PrintStack_char(s);
    cout << "]" << endl;

    list<int> neighbours_list = neighbours(u);
    cout << "neighbours(" << (char)(u + 'A' - 1) << ") = [ ";
    PrintList_char(neighbours_list);
    cout << "]" << endl;

    while (!neighbours_list.empty())
    {
        int v = neighbours_list.front();
        neighbours_list.pop_front();
        if (!num[v])
        {
            cout << "Chua duyet" << endl;
            scc_char(v, k, on_stack, num, min_num);
            min_num[u] = min(min_num[u], min_num[v]);
            cout << "min_num[" << (char)(u + 'A' - 1) << "] = min(min_num[" << (char)(u + 'A' - 1) << "]"
                 << ", min_num[" << (char)(v + 'A' - 1) << "]) = " << min(min_num[u], min_num[v]) << endl;
            ;
        }
        else if (on_stack[v])
        {
            cout << "Da duyet, con tren ngan xep" << endl;
            min_num[u] = min(min_num[u], num[v]);

            cout << "min_num[" << (char)(u + 'A' - 1) << "] = min(min_num[" << (char)(u + 'A' - 1) << "], num[" << (char)(v + 'A' - 1) << "]) = " << min_num[u] << endl;
        }
        else
            cout << "Bo qua" << endl;
    }

    if (num[u] == min_num[u])
    {
        cout << "num[" << (char)(u + 'A' - 1) << "] == min_num[" << (char)(u + 'A' - 1) << "]" << endl;
        cout << "\t\t\t\t\tpops = [ ";
        while (s.top() != u)
        {
            on_stack[s.top()] = false;
            cout << (char)(s.top() + 'A' - 1) << " ";
            s.pop();
        }
        on_stack[s.top()] = false;
        cout << (char)(s.top() + 'A' - 1) << "]" << endl;
        s.pop();

        cout << "stack = [ ";
        PrintStack_char(s);
        cout << "]" << endl;
    }
    else
    {
        cout << "num[" << (char)(u + 'A' - 1) << "] != min_num[" << (char)(u + 'A' - 1) << "]" << endl;
    }
}
