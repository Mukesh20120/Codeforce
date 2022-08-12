#include <bits/stdc++.h>

using namespace std;

class segmentmini{
    private:
        vector<int> seg;
    public:
     segmentmini(int n){
         seg.resize(4 * n);
     }
     void build(int node,int st,int en,int arr[]){
        if(st==en){
            seg[node] = arr[st];
            return;
        }
        int mid = (st + en) >> 1;
        build(2 * node + 1, st, mid, arr);
        build(2 * node + 2, mid + 1, en, arr);

        seg[node] = min(seg[2 * node + 1], seg[2 * node + 2]);
     }
     void update(int node,int st,int en,int idx,int val){
        if(st==en){
            seg[node] = val;
            return;
        }
        int mid = (st + en) >> 1;
        if(idx<=mid)
            update(2 * node + 1, st, mid, idx, val);
        else
            update(2 * node + 2, mid + 1, en, idx, val);

        seg[node] = min(seg[2 * node + 1], seg[2 * node + 2]);
     }
     int query(int node,int st,int en,int l,int r){
        //l r st en or st en l r
        if(r<st || en<l)
            return INT_MAX;
        //l st en r
        if(l<=st && en<=r)
            return seg[node];
        int mid = (st + en) >> 1;
        int lchild = query(2 * node + 1, st, mid, l, r);
        int rchild = query(2 * node + 2, mid + 1, en, l, r);
        return min(lchild, rchild);
     }
};

int main(){
    int n, m;
    cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n;i++)
        cin >> arr[i];
    segmentmini s(n);
    s.build(0, 0, n - 1, arr);
    while(m--){
        int q;
        cin >> q;
        if(q==1){
            int idx, val;
            cin >> idx >> val;
            s.update(0, 0, n - 1, idx, val);
        }
        else if(q==2){
            int l, r;
            cin >> l >> r;
            cout << s.query(0, 0, n - 1, l, r-1) << endl;
        }
    }

    return 0;
}