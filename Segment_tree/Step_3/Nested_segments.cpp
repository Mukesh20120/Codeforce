#include <bits/stdc++.h>

using namespace std;

struct trip
{
    int l, r, i;
};

static bool cmp(struct trip a, struct trip b)
{
    return a.r < b.r;
}

class SGTSUM{
    private:
        vector<int> seg;
    public:
     SGTSUM(int n){
         seg.resize(4 * n);
     }
     //we just need update and query function
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
        //st en l r or l r st en
        if(en<l || r<st)
            return 0;
        //complete overlap
        if(l<=st && en<=r)
            return seg[i];
        int mid = (st + en) >> 1;
        int lchild = query(2 * i + 1, st, mid, l, r);
        int rchild = query(2 * i + 2, mid + 1, en, l, r);
        return lchild + rchild;
     }
};

int main()
{
    // input from user

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;
    vector<int> nums(2 * n);
    for (int i = 0; i < 2 * n; i++)
        cin >> nums[i];
    // store in our vector so we can sort it range and index
    struct trip t;
    t.l = t.r = -1;
    vector<trip> temp(n, t);
    for (int i = 0; i < 2 * n; i++)
    {
        if (temp[nums[i] - 1].l == -1)
        {
            temp[nums[i] - 1].l = i;
        }
        else
        {
            temp[nums[i] - 1].r = i;
        }
        temp[nums[i] - 1].i = nums[i];
    }
    // sort according to there right index ascending order
    sort(temp.begin(), temp.end(), cmp);

    // for(auto it: temp)
    //     cout << it.l << " " << it.r << " " << it.i << "\n";
    SGTSUM st(2 * n);
    vector<int> ans(n);
    //traverse through the range and find the query and then update
    for(auto &it: temp){
        ans[it.i - 1] = st.query(0, 0, 2 * n - 1, it.l, it.r);
        st.update(0, 0, 2 * n - 1, it.l);
    }

    for(auto &it: ans)
        cout << it << " ";

    return 0;
}




//we don't need to store the input in first place in other vector we directly start stroing the range and index of that value as it entered

#include <bits/stdc++.h>

using namespace std;

struct trip
{
    int l, r, i;
};

static bool cmp(struct trip a, struct trip b)
{
    return a.r < b.r;
}

class SGTSUM
{
private:
    vector<int> seg;

public:
    SGTSUM(int n)
    {
        seg.resize(4 * n);
    }
    // we just need update and query function
    void update(int i, int st, int en, int idx)
    {
        if (st == en)
        {
            seg[i] = 1;
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid)
            update(2 * i + 1, st, mid, idx);
        else
            update(2 * i + 2, mid + 1, en, idx);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }
    int query(int i, int st, int en, int l, int r)
    {
        // st en l r or l r st en
        if (en < l || r < st)
            return 0;
        // complete overlap
        if (l <= st && en <= r)
            return seg[i];
        int mid = (st + en) >> 1;
        int lchild = query(2 * i + 1, st, mid, l, r);
        int rchild = query(2 * i + 2, mid + 1, en, l, r);
        return lchild + rchild;
    }
};

int main()
{
    // input from user

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;
    struct trip t;
    t.l = t.r = -1;
    vector<trip> temp(n, t);
    for (int i = 0; i < 2 * n; i++)
    {
        int input;
        cin >> input;

        if (temp[input-1].l == -1)
        {
            temp[input-1].l = i;
        }
        else
        {
            temp[input-1].r = i;
        }
        temp[input-1].i =input;
    }
    // sort according to there right index ascending order
    sort(temp.begin(), temp.end(), cmp);

   
    SGTSUM st(2 * n);
    vector<int> ans(n);
    // traverse through the range and find the query and then update
    for (auto &it : temp)
    {
        ans[it.i - 1] = st.query(0, 0, 2 * n - 1, it.l, it.r);
        st.update(0, 0, 2 * n - 1, it.l);
    }

    for (auto &it : ans)
        cout << it << " ";

    return 0;
}