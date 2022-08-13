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
        seg[i] = max(seg[2 * i + 1], seg[2 * i + 2]);
    }

    void update(int i, int st, int en, int idx, int val)
    {
        if (st == en)
        {
            seg[i] = val;
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid)
            update(2 * i + 1, st, mid, idx, val);
        else
            update(2 * i + 2, mid + 1, en, idx, val);
        seg[i] = max(seg[2 * i + 1], seg[2 * i + 2]);
    }
    int query(int i, int st, int en, int l,int r)
    {   //l r st en or st en l r
        if(r<st || en<l)
            return INT_MIN;
        if(l<=st && en<=r)
            return seg[i];
        int mid = (st + en) >> 1;
        int lchild = query(2 * i + 1, st, mid, l, r);
        int rchild = query(2 * i + 2, mid + 1, en, l, r);
        return max(lchild, rchild);
    }
  
};

int main()
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
        int q;
        cin >> q;
        if (q == 1)
        {
            int i, v;
            cin >> i >> v;
            arr[i] = v;
            st.update(0, 0, n - 1, i, v);
        }
        else
        {
            int x;
            cin >> x;
           //here we use binary search
            int ans = n;
            int low = 0, high = n - 1;
            while(low<=high){
                int mid = low + (high - low) / 2;
                if(x>st.query(0,0,n-1,low,mid))
                    low = mid + 1;
                else{
                    high = mid-1;
                    ans = min(ans, mid);
                }
            }
            if(ans==n)
                cout << -1 << "\n"
                     << flush;
            else
                cout << ans << "\n"
                     << flush;
        }
    }

    return 0;
}