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

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

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

    public:
    SegtreeLazy(const std::vector<node_seg> &A) : n(A.size()) {
        seg.resize(4*n, node_seg::inf());
        lazy.resize(4*n, node_lazy::inf());
        init(1, 0, n, A);
    }
    void update(const index_t l, const index_t r, const node_query &x) { update(1, 0, n, l, r, x); }
    node_seg query(const index_t l, const index_t r) { return query(1, 0, n, l, r); }
};

class HLD {
private:
    vector<vector<int>> adj;
    vector<int> in, sz, par, top, depth;
    void traverse1(int u) {
        sz[u] = 1;
        for (int &v: adj[u]) {
            adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
            depth[v] = depth[u] + 1;
            traverse1(v);
            par[v] = u;
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
        }
    }
    void traverse2(int u) {
        static int n = 0;
        in[u] = n++;
        for (int v: adj[u]) {
            top[v] = (v == adj[u][0] ? top[u] : v);
            traverse2(v);
        }
    }
public:
    void link(int u, int v) { // u and v is 1-based
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void init() { // have to call after linking
        top[1] = 1;
        traverse1(1);
        traverse2(1);
    }
    // u is 1-based and returns dfs-order [s, e) 0-based index
    pii subtree(int u) {
        return {in[u], in[u] + sz[u]};
    }
    // u and v is 1-based and returns array of dfs-order [s, e) 0-based index
    vector<pii> path(int u, int v) {
        vector<pii> res;
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            res.emplace_back(in[top[u]], in[u] + 1);
            u = par[top[u]];
        }
        res.emplace_back(min(in[u], in[v]), max(in[u], in[v]) + 1);
        return res;
    }
    HLD(int n) { // n is number of vertexes
        adj.resize(n+1); depth.resize(n+1);
        in.resize(n+1); sz.resize(n+1);
        par.resize(n+1); top.resize(n+1);
    }
};

typedef struct Node_lazy {
    unsigned int a, b;
    static Node_lazy inf() { return {1LL, 0LL}; }
    void operator+=(const Node_lazy &y) { a = a*y.a, b = b*y.a+y.b; }
} Node_lazy;

typedef struct Node_seg {
    unsigned int a;
    static Node_seg inf() { return {0LL}; }
    Node_seg operator+(const Node_seg &y) const { return {a+y.a}; }
    void operator()(const Node_lazy &y, const int s, const int e) { a = y.a*a+y.b*(e-s); }
} Node_seg;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    HLD hld(n);
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        hld.link(x, y);
    }
    hld.init();
    SegtreeLazy<Node_seg, Node_lazy> seg(vector<Node_seg>(n, Node_seg::inf()));
    while(q--) {
        int t; cin >> t;
        pii subt;
        vector<pii> path;
        int x, y;
        Node_lazy v = Node_lazy::inf();
        switch(t) {
            case 1:
            cin >> x >> v.b;
            subt = hld.subtree(x);
            seg.update(subt.fi, subt.se, v);
            break;

            case 2:
            cin >> x >> y >> v.b;
            path = hld.path(x, y);
            for(auto i : path) seg.update(i.fi, i.se, v);
            break;

            case 3:
            cin >> x >> v.a;
            subt = hld.subtree(x);
            seg.update(subt.fi, subt.se, v);
            break;

            case 4:
            cin >> x >> y >> v.a;
            path = hld.path(x, y);
            for(auto i : path) seg.update(i.fi, i.se, v);
            break;

            case 5:
            cin >> x;
            subt = hld.subtree(x);
            cout << seg.query(subt.fi, subt.se).a << "\n";
            break;

            case 6:
            cin >> x >> y;
            path = hld.path(x, y);
            unsigned int ans = 0;
            for(auto i : path) ans += seg.query(i.fi, i.se).a;
            cout << ans << "\n";
            break;
        }
    }
    return 0;
}