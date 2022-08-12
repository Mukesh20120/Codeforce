#include <bits/stdc++.h>

using namespace std;

class segmentsum{
	private:
		vector<long long>seg;
	public:
		segmentsum(int n){
			seg.resize(4*n);
		}
   void build(int node,int start,int end,int arr[]){
     if(start==end){
      seg[node]=arr[start];
      return;
	 }
	 int mid=(start+end)>>1;
	 build(2*node+1,start,mid,arr);
     build(2*node+2,mid+1,end,arr);
     seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
   }
   void update(int node,int start,int end,int idx,int val){
    if(start==end){
        seg[node] = val;
        return;
    }
    int mid = (start + end) >> 1;
    if(idx<=mid)
        update(2 * node + 1, start, mid, idx, val);
    else
        update(2 * node + 2, mid + 1, end, idx, val);
    seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
   }
   long long query(int node,int start,int end,int left,int right){
    //3 case
    //left right start end or start end left right
    if(right<start || end<left)
        return 0;
    //left start end right
    if(left<=start && end<=right)
        return seg[node];
    int mid = (start + end) >> 1;
    long long lchild = query(2 * node + 1, start, mid, left, right);
    long long rchild = query(2 * node + 2, mid + 1, end, left, right);
    return lchild + rchild;
   }
		
};

int main(){
    int n, m;
    cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n;i++)
        cin >> arr[i];
    segmentsum s(n);
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
            cout<<s.query(0, 0, n - 1, l, r-1)<<endl;
        }
    }
    return 0;
}