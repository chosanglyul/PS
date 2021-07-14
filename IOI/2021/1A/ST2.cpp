#include "candies.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class segtree {
private:
    int n;
    vector<ll> seg;
    void update(int i, int s, int e, int j, int x) {
        if(j < s || j >= e) return;
        else if(s+1 == e) seg[i] += x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    ll query(int i, int s, int e, int l, int r) {
        if(l >= e || s >= r) return 0LL;
        else if(l <= s && e <= r) return seg[i];
        else return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }
public:
    segtree(int m) {
        n = m;
        seg.resize(4*n);
        for(auto &i : seg) i = 0;
    }
    void update(int l, int r, int x) {
        update(1, 0, n, l, x);
        update(1, 0, n, r, -x);
    }
    ll query(int r) { return query(1, 0, n, 0, r); }
};

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v) {
    segtree s(c.size());
    for(int i = 0; i < v.size(); i++)
        s.update(l[i], r[i]+1, v[i]);
    vector<int> ans(c.size());
    for(int i = 0; i < c.size(); i++)
        ans[i] = (int)min((ll)c[i], s.query(i+1));
    return ans;
}
