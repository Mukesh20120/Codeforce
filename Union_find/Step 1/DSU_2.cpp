#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    // parent,size,minimal,maximal of the set
    int p, s, mini, maxi;
    node()
    {
        p = s = mini = maxi = 0;
    }
};

class DSU2
{
private:
    vector<node> parent;
    vector<int> rank;

public:
    DSU2(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        create();
    }
    void create()
    {
        for (int i = 0; i < parent.size(); i++)
        {
            parent[i].p = i;
            parent[i].s = 1;
            parent[i].mini = i;
            parent[i].maxi = i;
        }
    }
    int get(int n)
    {
        if (parent[n].p == n)
            return n;
        return parent[n].p = get(parent[n].p);
    }
    void makeunion(int u, int v)
    {
        u = get(u);
        v = get(v);
        if (u == v)
            return;
        // same check rank and merge
        if (rank[u] < rank[v])
        {
            parent[v].s += parent[u].s;
            parent[v].mini = min(parent[v].mini, parent[u].mini);
            parent[v].maxi = max(parent[v].maxi, parent[u].maxi);
            parent[u].p = v;
        }
        else if (rank[v] < rank[u])
        {
            parent[u].s += parent[v].s;
            parent[u].mini = min(parent[v].mini, parent[u].mini);
            parent[u].maxi = max(parent[v].maxi, parent[u].maxi);
            parent[v].p = u;
        }
        else
        {
            parent[u].s += parent[v].s;
            parent[u].mini = min(parent[v].mini, parent[u].mini);
            parent[u].maxi = max(parent[v].maxi, parent[u].maxi);
            parent[v].p = u;
            rank[u]++;
        }
    }
    node getparent(int u)
    {
        return parent[u];
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

//fast input output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); // flushes cout
                   /*
                   use printf and scanf instead of cin and cout
                   use '/n' instead of endl
                   cout<<endl=cout<<'/n'<<flush
                   */

    int n, m;
    cin >> n >> m;
    DSU2 uf(n);
    while (m--)
    {
        string s;
        cin >> s;
        if (s == "union")
        {
            int u, v;
            cin >> u >> v;
            uf.makeunion(u, v);
        }
        else
        {
            int u;
            cin >> u;
            node temp = uf.getparent(uf.get(u));
            cout << temp.mini << " " << temp.maxi << " " << temp.s << endl;
        }
    }

    return 0;
}