#include <bits/stdc++.h>

using namespace std;

class Unionfind
{
private:
    vector<int> parents;
    vector<int> rank;

public:
    Unionfind(int n)
    {
        parents.resize(n + 1);
        rank.resize(n + 1, 0);
        setparents();
    }
    void setparents()
    {
        for (int i = 0; i < parents.size(); i++)
            parents[i] = i;
    }
    int get(int node)
    {
        if (parents[node] == node)
            return node;
        return parents[node] = get(parents[node]);
    }
    void makeunion(int u, int v)
    {
        // first get the parent
        u = get(u);
        v = get(v);
        // now check rank
        if (rank[u] < rank[v])
        {
            // set parent of
            parents[u] = v;
        }
        else if (rank[v] < rank[u])
        {
            // set parent of v
            parents[v] = u;
        }
        else
        {
            parents[u] = v;
            rank[u]++;
        }
    }
    bool connected(int u, int v)
    {
        return get(u) == get(v);
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    Unionfind uf(n);
    while (m--)
    {
        int u, v;
        string s;
        cin >> s >> u >> v;
        if (s == "union")
            uf.makeunion(u, v);
        else
        {
            if (uf.connected(u, v))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }

    return 0;
}