#include <bits/stdc++.h>

using namespace std;

class SGTsum
{
private:
    vector<long long> seg;

public:
    SGTsum(int n)
    {
        seg.resize(4 * n, 0);
    }
    void update(int i, int st, int en, int idx, int val)
    {
        if (st == en)
        {
            seg[i]+= val;
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid)
            update(2 * i + 1, st, mid, idx, val);
        else
            update(2 * i + 2, mid + 1, en, idx, val);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }
    long long query(int i, int st, int en, int l, int r)
    {
        if (en < l || r < st)
            return 0;
        if (l <= st && en <= r)
            return seg[i];
        int mid = (st + en) >> 1;
        long long lchild = query(2 * i + 1, st, mid, l, r);
        long long rchild = query(2 * i + 2, mid + 1, en, l, r);
        return lchild + rchild;
    }
    void display(){
        for(auto &it: seg)
            cout << it << " ";
    }
};

int main()
{

    ios_base::sync_with_stdio(false);
   // cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;
    SGTsum st(n+1);
    while (m--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r, val;
            cin >> l >> r >> val;
             st.update(0, 0, n,l,val);
            st.update(0, 0, n , r, (-1*val));
        }
        else if (type == 2)
        {
            int idx;
            cin >> idx;
            cout << st.query(0, 0, n, 0, idx) << "\n";
        }
    }
    //st.display();

    return 0;
}