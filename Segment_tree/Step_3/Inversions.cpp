#include <bits/stdc++.h>
using namespace std;

class SGT{
    private:
    vector<int>seg;
    public:
    SGT(int n){
        seg.resize(4 * n);
    }
    void build(){

    }
    void update(int i,int st,int en,int idx){
        if(st==en){
            seg[i] = 1;
            return;
        }
        int mid = (st + en) >> 1;
        if(idx<=mid)
            update(2 * i + 1, st, mid, idx);
        else
            update(2 * i + 2, mid + 1, en, idx);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }
    int query(int i,int st,int en,int l,int r){
        //out of bound st en l r or l r st en
        if(en<l || r<st)
            return 0;
        if(l<=st && en<=r)
            return seg[i];
        int mid = (st + en) >> 1;
        int lchild = query(2 * i + 1, st, mid, l, r);
        int rchild = query(2 * i + 2, mid + 1, en, l, r);
        return lchild + rchild;
    }
};

int main(){

  //fast input and output
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  #ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif

  int n;
  cin >> n;
  int arr[n];
  SGT st(n+1);
  for (int i = 0; i < n; i++)
      cin >> arr[i];
  for (int i = 0; i <n; i++)
  {
      int a = st.query(0, 0, n, arr[i], n );
      cout << a << " ";
      st.update(0, 0, n , arr[i]);
    }
        return 0;
}