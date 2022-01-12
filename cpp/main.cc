#include "graph.h"

void set_false(bool arr[])
{
    for (int i = 0; i < 100; i++)
        arr[i] = false;
}

void set_zero(int arr[])
{
    for (int i = 0; i < 100; i++)
        arr[i] = 0;
}

void printArray(int *arr, int n)
{
    for (int *i = arr; i != (arr + n); i++)
        cout << *i << " ";

    cout << endl;
}

void print_path(int num[], int min_num[], int n)
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (num[i] <= num[j] && min_num[i] <= num[j] && min_num[j] <= num[i] && i != j)
                cout << i << " -> " << j << endl;
}

int main()
{
    graph g1((char *)"./graph.txt", true);

    int k = 1;
    bool on_stack[100];
    int num[100];
    int min_num[100];

    set_false(on_stack);
    set_zero(num);
    set_zero(min_num);

    g1.scc(4, k, on_stack, num, min_num);

    printArray(num + 1, g1.getN());
    printArray(min_num + 1, g1.getN());

    return 0;
}