#include <bits/stdc++.h>

using namespace std;

class node{
public:
    int ob;//open bracket
    int cb;//close bracket
    int full;//bracket

    node(){
        ob = 0;
        cb = 0;
        full = 0;
    }

};

node merge(node left,node right){
    node ans;
    int ef = min(left.ob, right.cb);
    ans.ob = left.ob + right.ob - ef;
    ans.cb = left.cb + right.cb - ef;
    ans.full = left.full + right.full + ef;
    return ans;
}

class SGT{
    private:
        vector<node> seg;
    public:
    SGT(int n){
        seg.resize(4 * n);
    }
    void build(int i,int st,int en,string &s){
          if(st==en){
              seg[i].ob = (s[st] == '(');
              seg[i].cb = (s[st] == ')');
              seg[i].full = 0;
              return;
          }
          int mid = (st + en) >> 1;
          build(2 * i + 1, st, mid, s);
          build(2 * i + 2, mid + 1, en, s);

          seg[i] = merge(seg[2 * i + 1], seg[2 * i + 2]);
    }
    node query(int i,int st,int en,int l,int r){
        //l r st en or st en l r
        if(r<st || en <l)
            return node();
        //l st en r
        if(l<=st && en<=r)
            return seg[i];
        int mid = (st + en) >> 1;
        node lchild = query(2 * i + 1, st, mid, l, r);
        node rchild = query(2 * i + 2, mid + 1, en, l, r);

        return merge(lchild,rchild);
    }
};

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string s;
    cin >> s;
    int n = s.length();
    SGT sg(n);
    sg.build(0, 0, n - 1, s);
    int m;
    cin >> m;
    while(m--){
        int l, r;
        cin >> l >> r;
        node temp = sg.query(0, 0, n - 1, l - 1, r - 1);
        cout <<temp.full*2<<endl;
    }

    return 0;
}