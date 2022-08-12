#include <bits/stdc++.h>

using namespace std;

class segmentsum
{
private:
    vector<int> seg;

public:
    segmentsum(int n)
    {
        seg.resize(4 * n, 0);
    }
    // we required node to seg st and end is our range and arr is our given array
    int build(int node, int start, int end, int *arr)
    {
        // base case
        if (start == end)
        {
            // as start and end are equal we take either of them
            seg[node] = arr[start];
            return arr[start];
        }
        // if it is not true then we find mid
        int mid = (start + end) >> 1;
        // calling left child with half left arr and right with other half
        // here we are taking 0 indexing 0 root 1 leftchild 2 rightchild then
        //  2*node +1=1 and 2*node+2=2 for 0 index
        // for 1 indexing  1 root 2 leftchild and 3 rightchild
        // 2*node=2 and 2*node+1=3
        int left = build(2 * node + 1, start, mid, arr);
        int right = build(2 * node + 2, mid + 1, end, arr);
        // this function change according to the given question
        seg[node] = left + right;
    }

    int query(int node, int start, int end, int left, int right)
    {
        // we have to check 3 base case
        // 1 if it is out of bound
        //  left right start end or start end left right
        if (right < start || end < left)
            return 0; // for sum it change according to question
        // 2 complete
        // left start end right
        if (left <= start && end <= right)
            return seg[node];
        // other wise 3 case partial segment
        int mid = (start + end) >> 1;
        int lchild = query(2 * node + 1, start, mid, left, right);
        int rchild = query(2 * node + 2, mid + 1, end, left, right);
        return lchild + rchild;
    }

    void update(int node, int start, int end, int idx, int val)
    {
        // base case
        if (start == end)
        {
            seg[node] = val;
            return;
        }
        int mid = (start + end) >> 1;
        // now we have two case
        if (idx <= mid)
        {
            // means the index
            update(2 * node + 1, start, mid, idx, val);
        }
        else
            update(2 * node + 2, mid + 1, end, idx, val);

        seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
    }
};

int main()
{

    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    // creating segment
    segmentsum seg1(4 * n + 1);
    seg1.build(0, 0, n - 1, arr);

    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << seg1.query(0, 0, n - 1, l, r) << endl;
    }

    return 0;
}