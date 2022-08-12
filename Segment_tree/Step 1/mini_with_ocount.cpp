#include <bits/stdc++.h>

using namespace std;

class segmentmini{
    private:
        vector<pair<int,int>> seg;
    public:
     segmentmini(int n){
         seg.resize(4 * n);
     }
     void build(int node,int st,int en,int arr[]){
        if(st==en){
            seg[node].first = arr[st];
            seg[node].second = 1;
            return;
        }
        int mid = (st + en) >> 1;
        build(2 * node + 1, st, mid, arr);
        build(2 * node + 2, mid + 1, en, arr);

    
        if(seg[2*node+1].first<seg[2*node+2].first)
            seg[node] = seg[2 * node + 1];
        else if(seg[2*node+1].first>seg[2*node+2].first)
            seg[node] = seg[2 * node + 2];
        else{
            seg[node].first = seg[2 * node + 1].first;
            seg[node].second = seg[2 * node + 1].second + seg[2 * node + 2].second;
        }
 }

     void update(int node,int st,int en,int idx,int val){
        if(st==en){
            seg[node].first = val;
            seg[node].second = 1;
            return;
        }
        int mid = (st + en) >> 1;
        if(idx<=mid)
            update(2 * node + 1, st, mid, idx, val);
        else
            update(2 * node + 2, mid + 1, en, idx, val);

        
        if(seg[2*node+1].first<seg[2*node+2].first)
            seg[node] = seg[2 * node + 1];
        else if(seg[2*node+1].first>seg[2*node+2].first)
            seg[node] = seg[2 * node + 2];
        else{
            seg[node].first = seg[2 * node + 1].first;
            seg[node].second = seg[2 * node + 1].second + seg[2 * node + 2].second;
        }
     }
     pair<int,int> query(int node,int st,int en,int l,int r){
        //l r st en or st en l r
        if(r<st || en<l)
            return {INT_MAX,0};
        //l st en r
        if(l<=st && en<=r)
            return seg[node];
        int mid = (st + en) >> 1;
        pair<int,int> lchild = query(2 * node + 1, st, mid, l, r);
        pair<int,int> rchild = query(2 * node + 2, mid + 1, en, l, r);
        pair<int, int> ans;
        if(lchild.first<rchild.first)
            ans= lchild;
        else if(lchild.first>rchild.first)
            ans= rchild;
        else{
            ans.first = lchild.first;
            ans.second = lchild.second + rchild.second;
        }
        return ans;
     }
};

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

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
            pair<int, int> t = s.query(0, 0, n - 1, l, r - 1);
            cout <<t.first<<" "<<t.second<< endl;
        }
    }

    return 0;
}