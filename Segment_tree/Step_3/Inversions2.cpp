#include <bits/stdc++.h>
using namespace std;
int n;
class SGT{
    private:
    vector<int>seg;
    public:
    SGT(int n){
        seg.resize(4 * n);
    }
    void build(int i,int st,int en){
      if(st==en){
          seg[i] = 1;
          return;
      }
      int mid = (st + en) >> 1;
      build(2 * i, st, mid);
      build(2 * i + 1,mid + 1, en);
      seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
    void update(int i,int st,int en,int idx){
        if(st==en){
            seg[i] = 0;
            return;
        }
        int mid = (st + en) >> 1;
        if(idx<=mid)
            update(2 * i , st, mid, idx);
        else
            update(2 * i+1, mid + 1, en, idx);
        seg[i] = seg[2 * i ] + seg[2 * i + 1];
    }
    int query(int i,int st,int en,int k){
       if(st==en){
        if(seg[i]==k)
            return st;
        else
            return n;
       }
       int mid = (st + en) >> 1;
       if(seg[2*i]>=k)
           return query(2 * i, st, mid, k);
       
     return query(2 * i + 1, mid + 1, en, k - seg[2 * i]);
    }
    void display(){
        for(int it: seg)
            cout << it << " ";
    }
    int get(){
        return seg[1];
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

 
  cin >> n;
  int arr[n];
  int ans[n];
  SGT st(n);
  for (int i = 0; i < n; i++)
      cin >> arr[i];
 
  st.build(1, 0, n-1);
  //st.display();
  for (int i = n-1; i>=0; i--)
  {
      int q = st.query(1, 0, n - 1, st.get() - arr[i]);
      ans[i] = q+1;
      st.update(1, 0, n - 1, max(q, 0));
    }
    for(int &it: ans)
        cout << it << " ";

        return 0;
}