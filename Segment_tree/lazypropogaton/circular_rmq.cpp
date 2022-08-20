#include <bits/stdc++.h>
#define ll long long

using namespace std;

class SGTlazysum
{
private:
    vector<ll> seg, lazy;

public:
    SGTlazysum(int n)
    {
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }
    void build(int i, int st, int en, ll arr[])
    {
        // same as segment tree build function
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
    long long query(int i, int st, int en, int l, int r)
    {
        // check lazy to update
        if (lazy[i] != 0)
        {
            // update the first attached
            seg[i] += (en - st - 1) * lazy[i];
            if (st != en)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
        // out of bound
        // st en l r or l r st en
        if (en < l || r < st)
            return 0;
        // complete
        if (l <= st && en <= r)
            return seg[i];
        int mid = (st + en) >> 1;
        ll leftchild = query(2 * i + 1, st, mid, l, r);
        ll rightchild = query(2 * i + 2, mid + 1, en, l, r);
        return leftchild + rightchild;
    }
    void update(int i, int st, int en, int l, int r, int val)
    {
        // check for the update in lazy
        if (lazy[i] != 0)
        {
            seg[i] += (en - st - 1) * lazy[i];
            if (st != en)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
        // no overlap
        // st en l r or l r st en
        if (en < l || r < st)
            return;

        if (l <= st && en <= r)
        {
            // complete in it we directly update the seg
            seg[i] += (en - st - 1) * val;
            if (st != en)
            {
                lazy[2 * i + 1] += val;
                lazy[2 * i + 2] += val;
            }
            return;
        }
        int mid = (st + en) >> 1;
        update(2 * i + 1, st, mid, l, r, val);
        update(2 * i + 2, mid + 1, en, l, r, val);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }
};

class SGTlazymin
{
private:
    vector<ll> seg, lazy;

public:
    SGTlazymin(int n)
    {
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }
    ll mini(ll a,ll b){
        if(a>b)
            return b;
        return a;
    }
    void build(int i, int st, int en, ll arr[])
    {
        // same as segment tree build function
        if (st == en)
        {
            seg[i] = arr[st];
            return;
        }
        int mid = (st + en) >> 1;
        build(2 * i + 1, st, mid, arr);
        build(2 * i + 2, mid + 1, en, arr);
        seg[i] = mini(seg[2 * i + 1],seg[2 * i + 2]);
    }
    long long query(int i, int st, int en, int l, int r)
    {
        // check lazy to update
        if (lazy[i] != 0)
        {
            // update the first attached
            seg[i] += lazy[i];
            if (st != en)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
        // out of bound
        // st en l r or l r st en
        if (en < l || r < st)
            return INT_MAX; 
        // complete
        if (l <= st && en <= r)
            return seg[i];
        int mid = (st + en) >> 1;
        ll leftchild = query(2 * i + 1, st, mid, l, r);
        ll rightchild = query(2 * i + 2, mid + 1, en, l, r);
        return mini(leftchild,rightchild);
    }
    void update(int i, int st, int en, int l, int r, int val)
    {
        // check for the update in lazy
        if (lazy[i] != 0)
        {
            seg[i] +=lazy[i];
            if (st != en)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
        // no overlap
        // st en l r or l r st en
        if (en < l || r < st)
            return;

        if (l <= st && en <= r)
        {
            // complete in it we directly update the seg
            seg[i] += val;
            if (st != en)
            {
                lazy[2 * i + 1] += val;
                lazy[2 * i + 2] += val;
            }
            return;
        }
        int mid = (st + en) >> 1;
        update(2 * i + 1, st, mid, l, r, val);
        update(2 * i + 2, mid + 1, en, l, r, val);
        seg[i] = mini(seg[2 * i + 1],seg[2 * i + 2]);
    }
};

ll givelongno(string s){
    int i = 0;
    ll ans = 0;
    int sign = 1;
    if(s[0]=='-'){
       i = 1;
       sign = -1;
    }
      
    for (; i < s.length();i++){
        ans = ans * 10 + (s[i]-'0');
    }
    return ans * sign;
}

int main()
{ 
    //fast input and out
    ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

   #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
   #endif

    int n, m;
    cin >> n;
    long long arr[n];
    for (int i = 0; i < n;i++)
        cin >> arr[i];

    SGTlazymin st(n);
    st.build(0, 0, n - 1, arr);
    cin >> m;
    cin.ignore();
    while(m--){
        string s;
        getline(cin, s);
        stringstream sso;
        sso << s;
        string left,right,val;
        getline(sso, left, ' ');
        getline(sso, right, ' ');
        getline(sso, val, ' ');
        int l = stoi(left);
        int r = stoi(right);
        if(val==""){
            // 0 r l n-1
            if(l>r)
                cout << min(st.query(0, 0, n - 1, 0, r), st.query(0, 0, n - 1, l, n - 1))<<"\n";
            else
                cout << st.query(0, 0, n - 1, l, r)<<"\n";
        }
        else{
            ll v = givelongno(val);
            //cout << "value" << v << "\n";
            // 0 r l n-1
            if(l>r){
                st.update(0, 0, n - 1, 0, r, v);
                st.update(0, 0, n - 1, l, n - 1,v);
            }
            else
                st.update(0, 0, n - 1, l, r,v);
        }
    }
    return 0;
}