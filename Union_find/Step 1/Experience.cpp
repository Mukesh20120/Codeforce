#include <bits/stdc++.h>
#define pr pair<int,int>
using namespace std;

class DSU
{
private:
    vector<int> par,exp,rank;
public:
    DSU(int n)
    {
        par.resize(n + 1);
        exp.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 1; i < par.size(); i++)
        {
            par[i] = i;
            exp[i] = 0;
            rank[i] = 0;
        }
    }
    pr get(int u)
    {
        if (par[u] == u)
            return {u,exp[u]};
        pr parent = get(par[u]);
        par[u] = parent.first;
        exp[u] = exp[u] + parent.second - exp[parent.first];
        return {par[u],exp[u]+exp[par[u]]};
    }
    void jointit(int u, int v)
    {
        u = get(u).first;
        v = get(v).first;

        if (u == v)
            return;
        // now compare rank and join then
        if (rank[u] < rank[v])
        {
            par[u] = v;
            exp[u] = exp[u] - exp[v];
        }

        else if (rank[v] < rank[u])
        {
            par[v] = u;
            exp[v] = exp[v] - exp[u];
        }
        else
        {
            par[u] = v;
            exp[u] = exp[u] - exp[v];
            rank[v]++;
        }
    }
    void add(int u, int ex)
    {
        int a = get(u).first;
        exp[a] += ex;
    }
};

int main()
{
    // fast input and output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
// input and output text file
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    while (m--)
    {
        string a;
        cin >> a;
        if (a == "add")
        {
            int u, v;
            cin >> u >> v;
            dsu.add(u, v);
        }
        else if (a == "join")
        {
            int u, v;
            cin >> u >> v;
            dsu.jointit(u, v);
        }
        else
        {
            int i;
            cin >> i;
            cout << dsu.get(i).second << "\n";
        }
    }

    return 0;
}