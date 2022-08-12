#include <bits/stdc++.h>
using namespace std;


class segmentxor
{
private:
    vector<int> segx;

public:
    segmentxor(int n)
    {
        segx.resize(4 * n);
    }
    int getval(){
        return segx[0];
    }

    void build(int node, int start, int end, int arr[], int isor)
    {
        if (start == end)
        {
            segx[node] = arr[start];
            return;
        }
        int mid = (start + end) >> 1;
        build(2 * node + 1, start, mid, arr, !isor);
        build(2 * node + 2, mid + 1, end, arr, !isor);
        // now we have two case
        if (isor)
            segx[node] = segx[2 * node + 1] | segx[2 * node + 2];
        else
            segx[node] = segx[2 * node + 1] ^ segx[2 * node + 2];
    }


    void update(int node, int start, int end, int idx, int val, int isor)
    {
        if (start == end)
        {
            segx[node] = val;
            return;
        }
        int mid = (start + end) >> 1;
        if (idx <= mid)
            update(2 * node + 1, start, mid, idx, val, !isor);
        else
            update(2 * node + 2, mid + 1, end, idx, val, !isor);

        if (isor)
            segx[node] = segx[2 * node + 1] | segx[2 * node + 2];
        else
            segx[node] = segx[2 * node + 1] ^ segx[2 * node + 2];
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    int el = pow(2, n);
    int arr[el];
    for (int i = 0; i < el;i++)
        cin >> arr[i];

    segmentxor seg(el);
    if(n%2==0)
        seg.build(0, 0, el - 1, arr, 0);
    else
        seg.build(0, 0, el - 1, arr, 1);

     while (m--){
         int i, val;
         cin >> i >> val;
         i--;
         if(n%2==0)
             seg.update(0, 0, el - 1, i, val, 0);
        else
             seg.update(0, 0, el - 1, i, val, 1);

        cout << seg.getval() << endl;
     }
        

    return 0;
}