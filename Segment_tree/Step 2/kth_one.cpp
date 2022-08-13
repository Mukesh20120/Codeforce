#include <bits/stdc++.h>
using namespace std;

class SGT
{
private:
    vector<int> seg;

public:
    SGT(int n)
    {
        seg.resize(4 * n);
    }
    void update(int i, int st, int en, int idx)
    {
        if (st == en)
        {
            seg[i] = !seg[i];
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid)
            update(2 * i + 1, st, mid, idx);
        else
            update(2 * i + 2, mid + 1, en, idx);
        // we will update our segment
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }
    void build(int i, int st, int en, int arr[])
    {
        if (st == en)
        {
            seg[i] = arr[st];
            return;
        }
        int mid = (st + en) >> 1;
        build(2 * i + 1, st, mid, arr);
        build(2 * i + 2, mid + 1, en, arr);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }
    int query(int i, int st, int en, int k)
    {
        // complete
        if (st == en)
        {
            return st;
        }
        int mid = (st + en) >> 1;
        if (seg[2 * i + 1] > k)
            return query(2 * i + 1, st, mid, k);
        else
            return query(2 * i + 2, mid + 1, en, k - seg[2 * i + 1]);
    }
};

int
main()
{
    // fast input and output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

// input and output file
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    SGT st(n);
    st.build(0, 0, n - 1, arr);
    while (m--)
    {
        int q, o;
        cin >> q >> o;
        if (q == 1)
            st.update(0, 0, n - 1, o);
        else
        {
            cout << st.query(0, 0, n - 1, o) << "\n"
                 << flush;
        }
    }

    return 0;
}