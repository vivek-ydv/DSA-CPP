#include <bits/stdc++.h>
using namespace std;

// A data type to store all these, we can also use tuples insted of this
struct node
{
    int u;
    int v;
    int wt;
    node(int first, int second, int weight)
    {
        u = first;
        v = second;
        wt = weight;
    }
};
// Compartor function to sort according to weight
static bool comp(node a, node b)
{
    return a.wt < b.wt;
}
// Disjoint data structure implementation
int findPar(int u, vector<int> &parent)
{
    if (u == parent[u])
        return u;
    return parent[u] = findPar(parent[u], parent); // Path compression
}
void unionn(int u, int v, vector<int> &parent, vector<int> &rank)
{
    int x = findPar(u, parent);
    int y = findPar(v, parent);
    if (rank[x] < rank[y])
    {
        parent[x] = y;
    }
    else if (rank[y] < rank[x])
    {
        parent[y] = x;
    }
    else
    {
        parent[y] = x;
        rank[x]++;
    }
}

// Code for kruskals algorithm : Driver code
int main()
{
    int N = 5, m = 6;
    vector<node> edges;
    edges.push_back(node(0, 1, 2));
    edges.push_back(node(0, 3, 6));
    edges.push_back(node(1, 0, 2));
    edges.push_back(node(1, 2, 3));
    edges.push_back(node(1, 3, 8));
    edges.push_back(node(1, 4, 5));
    edges.push_back(node(2, 1, 3));
    edges.push_back(node(2, 4, 7));
    edges.push_back(node(3, 0, 6));
    edges.push_back(node(3, 1, 8));
    edges.push_back(node(4, 1, 5));
    edges.push_back(node(4, 2, 7));
    sort(edges.begin(), edges.end(), comp); // sort by weights

    vector<int> parent(N);
    for (int i = 0; i < N; i++)
        parent[i] = i;
    vector<int> rank(N, 0);

    // Kruskals algorithm
    int cost = 0;
    vector<pair<int, int>> mst;
    for (auto it : edges)
    {
        if (findPar(it.v, parent) != findPar(it.u, parent)) // if both vertex donot have the same component
        {
            cost += it.wt;
            mst.push_back({it.u, it.v});
            unionn(it.u, it.v, parent, rank);
        }
    }
    cout << cost << endl;
    for (auto it : mst)
        cout << it.first << " - " << it.second << endl;
    return 0;
}