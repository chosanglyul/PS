#include "candies.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

template <typename node_seg, typename node_lazy, typename node_query = node_lazy, typename index_t = int>
class SegtreeLazy {
    private:
    const size_t n;
    std::vector<node_seg> seg;
    std::vector<node_lazy> lazy;

    void prop(const size_t i, const index_t s, const index_t e) {
        if(!(s+1 == e)) {
            lazy[i<<1] += lazy[i];
            seg[i<<1](lazy[i], s, s+e>>1);
            lazy[i<<1|1] += lazy[i];
            seg[i<<1|1](lazy[i], s+e>>1, e);
        }
        lazy[i] = node_lazy::inf();
    }

    void init(const size_t i, const index_t s, const index_t e, const std::vector<node_seg> &A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }

    void update(const size_t i, const index_t s, const index_t e, const index_t l, const index_t r, const node_query &x) {
        prop(i, s, e);
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i](x, s, e);
            lazy[i] += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }

    node_seg query(const size_t i, const index_t s, const index_t e, const index_t l, const index_t r) {
        prop(i, s, e);
        if(r <= s || e <= l) return node_seg::inf();
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    index_t search(const size_t i, const index_t s, const index_t e, const function<bool(const node_seg&)> &F, const node_seg &x) {
        prop(i, s, e);
        if(s+1 == e) return s;
        const node_seg y = seg[i<<1|1]+x;
        if(F(y)) return search(i<<1|1, s+e>>1, e, F, x);
        return search(i<<1, s, s+e>>1, F, y);
    }

    public:
    SegtreeLazy(const std::vector<node_seg> &A) : n(A.size()) {
        seg.resize(4*n, node_seg::inf());
        lazy.resize(4*n, node_lazy::inf());
        init(1, 0, n, A);
    }
    void update(const index_t l, const index_t r, const node_query &x) { update(1, 0, n, l, r, x); }
    node_seg query(const index_t l, const index_t r) { return query(1, 0, n, l, r); }
    index_t search(const function<bool(const node_seg&)> &F) { return search(1, 0, n, F, node_seg::inf()); }
    void print() {
        for(auto i : seg) cout << i.mi << " " << i.ma << "  "; cout << "\n";
        for(auto i : lazy) cout << i.x << " "; cout << "\n";
    }
};

struct Node_lazy {
    ll x;
    static Node_lazy inf() { return {0LL}; }
    void operator+=(const Node_lazy &y) { x += y.x; }
};

struct Node_seg {
    ll mi, ma;
    static Node_seg inf() { return {LLINF, -LLINF}; }
    Node_seg operator+(const Node_seg &y) { return {min(mi, y.mi), max(ma, y.ma)}; }
    void operator()(const Node_lazy &y, const int l, const int r) { mi += y.x, ma += y.x; }
};

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v) {
    int n = c.size(), q = v.size();
    vector<vector<int>> L(n), R(n);
    for(int i = 0; i < q; i++) {
        L[l[i]].push_back(i);
        R[r[i]].push_back(i);
    }
    vector<int> ans(n);
    SegtreeLazy<Node_seg, Node_lazy> S(vector<Node_seg>(q+1, {0LL, 0LL}));
    for(int i = 0; i < n; i++) {
        for(auto j : L[i]) S.update(j+1, q+1, {v[j]});
        Node_seg full_range = S.query(0, q+1);
        ll su = S.query(q, q+1).mi;
        if(full_range.ma-full_range.mi <= c[i]) {
            if(full_range.mi < 0) ans[i] = su-full_range.mi;
            else if(full_range.ma > c[i]) ans[i] = c[i]-(full_range.ma-su);
            else ans[i] = su;
        } else {
            int idx = S.search([&](const Node_seg &seg) { return seg.ma-seg.mi > c[i]; });
            full_range = S.query(idx+1, q+1);
            assert(full_range.ma-full_range.mi <= c[i]);
            if(v[idx] < 0) ans[i] = su-full_range.mi;
            else ans[i] = c[i]-(full_range.ma-su);
            //cout << c[i] << " " << idx << " " << pre << " " << v[idx] << "\n";
        }
        for(auto j : R[i]) S.update(j+1, q+1, {-v[j]});
    }
    //cout << S.query(0, q+1).mi << " " << S.query(0, q+1).ma << "\n";
    return ans;
}
