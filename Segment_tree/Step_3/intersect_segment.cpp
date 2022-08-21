#include <bits/stdc++.h>

using namespace std;

struct trip
{
    int l, r, i;
};
static bool cmp(struct trip a, struct trip b)
{
    return a.r < b.r;
}
class SGTsum
{
private:
    vector<int> seg;

public:
    SGTsum(int n)
    {
        seg.resize(4 * n);
    }
    void update(int i, int st, int en, int idx)
    {
        if (st == en)
        {
            seg[i] = 1;
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid)
            update(2 * i + 1, st, mid, idx);
        else
            update(2 * i + 2, mid + 1, en, idx);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }
    int query(int i, int st, int en, int l, int r)
    {
        // st en l r or l r st en
        if (en < l || r < st)
            return 0;
        if (l <= st && en <= r)
            return seg[i];
        int mid = (st + en) >> 1;
        int lchild = query(2 * i + 1, st, mid, l, r);
        int rchild = query(2 * i + 2, mid + 1, en, l, r);
        return lchild + rchild;
    }
    void display(){
        for(auto it: seg)
            cout << it << " ";
    }
};

int main()
{

    // fast input and output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;
    int arr[2 * n];
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> arr[i];
    }
    SGTsum st(2 * n);
    struct trip t;
    t.l = t.r = -1;
    vector<trip> temp(n, t);
    // make temp store range and number
    for (int i = 0; i < 2 * n; i++)
    {
        if (temp[arr[i] - 1].l == -1)
            temp[arr[i] - 1].l = i;
        else
            temp[arr[i] - 1].r = i;
        temp[arr[i] - 1].i = arr[i];
    }
    sort(temp.begin(), temp.end(), cmp);
    vector<int> ans(n);
   // st.display();
    for (auto it : temp)
    {
        //     cout << it.l << " " << it.r << " " << it.i << "\n";
         int a= st.query(0, 0, 2 * n - 1, it.l, it.r);
         ans[it.i - 1] = (it.r - it.l - 1) - (2 * a);
         st.update(0, 0, 2 * n - 1, it.l);
    }
    for (int &it : ans)
        cout << it << " ";
    return 0;
}