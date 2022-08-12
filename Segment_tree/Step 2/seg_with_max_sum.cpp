#include <bits/stdc++.h>
using namespace std;
#define ll long long
class node
{  public:
    ll sum, pre, suf, ans;
    node(){
        sum = pre = suf = ans = 0;
    }
};

class SGT
{
private:
    vector<node> seg;

public:
    SGT(int n)
    {
        seg.resize(4 * n);
    }
    ll getans(){
        return seg[0].ans;
    }
    void build(int i, int st, int en, ll arr[])
    {
        if (st == en)
        {
            if (arr[st] < 0){
                seg[i].ans = 0;
                seg[i].pre = 0;
                seg[i].suf = 0;
            }
            else{
                seg[i].ans = arr[st];
                seg[i].pre = arr[st];
                seg[i].suf = arr[st];
            }
            seg[i].sum = arr[st];
            return;
        }
        int mid = (st + en) >> 1;
        build(2 * i + 1, st, mid, arr);
        build(2 * i + 2, mid + 1, en, arr);

        seg[i].sum = seg[2 * i + 1].sum + seg[2 * i + 2].sum;
        seg[i].pre = max(seg[2 * i + 1].pre, seg[2 * i + 1].sum + seg[2 * i + 2].pre);
        seg[i].suf = max(seg[2 * i + 2].suf, seg[2 * i + 2].sum + seg[2 * i + 1].suf);
        seg[i].ans = max(seg[2 * i + 1].ans, max(seg[2 * i + 2].ans, seg[2 * i + 1].suf + seg[2 * i + 2].pre));
    
    }
    void update(int i,int st,int en,int idx,ll val,ll arr[]){
         if (st == en)
        {
            arr[st] = val;
            if (arr[st] <= 0){
                seg[i].ans = 0;
                seg[i].pre = 0;
                seg[i].suf = 0;
            }
            else{
                seg[i].ans = arr[st];
                seg[i].pre = arr[st];
                seg[i].suf = arr[st];
            }
            seg[i].sum = arr[st];
            return;
        }
        int mid = (st + en) >> 1;
        if(idx<=mid)
            update(2 * i + 1, st, mid, idx, val, arr);
        else
            update(2 * i + 2, mid + 1, en, idx, val, arr);

         seg[i].sum = seg[2 * i + 1].sum + seg[2 * i + 2].sum;
        seg[i].pre = max(seg[2 * i + 1].pre, seg[2 * i + 1].sum + seg[2 * i + 2].pre);
        seg[i].suf = max(seg[2 * i + 2].suf, seg[2 * i + 2].sum + seg[2 * i + 1].suf);
        seg[i].ans = max(seg[2 * i + 1].ans, max(seg[2 * i + 2].ans, seg[2 * i + 1].suf + seg[2 * i + 2].pre));
    
    }
};

int
main()
{
    // for fast input and output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

// file input and output
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    ll arr[n];
    for (int i = 0; i < n; i++)
        scanf("%lld", &arr[i]);
    SGT s(n);
    s.build(0, 0, n - 1, arr);
    printf("%lld\n", s.getans());
   while(m--){
       int i;
       ll val;
       scanf("%d%lld", &i, &val);
       s.update(0, 0, n - 1, i, val, arr);
       printf("%lld\n", s.getans());
   }
    return 0;
}