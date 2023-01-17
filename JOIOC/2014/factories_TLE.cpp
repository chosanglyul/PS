#include "factories.h"
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
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

class segtree {
    private:
    int n;
    vector<int> modi, chk;
    vector<ll> seg, lazy, dep;
    void upd_node(int i) {
        if(!chk[i]) {
            chk[i] = 1;
            modi.push_back(i);
        }
    }

    void init(int i, int s, int e, vector<ll> &B) {
        seg[i] = lazy[i] = LLINF;
        chk[i] = 0;
        if(s+1 == e) dep[i] = B[s];
        else {
            init(i<<1, s, s+e>>1, B);
            init(i<<1|1, s+e>>1, e, B);
            dep[i] = max(dep[i<<1], dep[i<<1|1]);
        }
    }

    void prop(int i, int s, int e) {
        if(s+1 < e && lazy[i] < LLINF) {
            upd_node(i<<1);
            lazy[i<<1] = min(lazy[i<<1], lazy[i]);
            seg[i<<1] = min(seg[i<<1], lazy[i]-2*dep[i<<1]);
            upd_node(i<<1|1);
            lazy[i<<1|1] = min(lazy[i<<1|1], lazy[i]);
            seg[i<<1|1] = min(seg[i<<1|1], lazy[i]-2*dep[i<<1|1]);
        }
        lazy[i] = LLINF;
    }

    void update(int i, int s, int e, int l, int r, ll x){
        prop(i, s, e);
        if(r <= s || e <= l) return;
        upd_node(i);
        if(l <= s && e <= r) {
            lazy[i] = min(lazy[i], x);
            seg[i] = min(seg[i], x-2*dep[i]);
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }

    ll query(int i, int s, int e, int l, int r) {
        prop(i, s, e);
        if(r <= s || e <= l) return LLINF;
        if(l <= s && e <= r) return seg[i];
        return min(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree() {}
    segtree(vector<ll> &B) {
        n = B.size();
        seg.resize(4*n);
        lazy.resize(4*n);
        dep.resize(4*n);
        chk.resize(4*n);
        init(1, 0, n, B);
    }

    void update(int l, int r, ll x) { update(1, 0, n, l, r, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }

    void clear() {
        for(auto i : modi) {
            seg[i] = lazy[i] = LLINF;
            chk[i] = 0;
        }
        modi.clear();
    }
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
    HLD() {}
    HLD(int n) { // n is number of vertexes
        adj.resize(n+1); depth.resize(n+1);
        in.resize(n+1); sz.resize(n+1);
        par.resize(n+1); top.resize(n+1);
    }
};

void dfs(int x, ll d, vector<ll> &dep, vector<bool> &vis, vector<vector<pii>> &E) {
    if(vis[x]) return;
    vis[x] = true;
    dep[x] = d;
    for(auto i : E[x]) dfs(i.fi, d+i.se, dep, vis, E);
}

segtree seg;
HLD hld;
vector<ll> dep;

void Init(int N, int A[], int B[], int D[]) {
    hld = HLD(N);
    vector<vector<pii>> E(N);
    for(int i = 0; i < N-1; i++) {
        E[A[i]].push_back({B[i], D[i]});
        E[B[i]].push_back({A[i], D[i]});
        hld.link(A[i]+1, B[i]+1);
    }
    hld.init();
    dep.resize(N);
    vector<bool> vis(N, false);
    dfs(0, 0LL, dep, vis, E);
    vector<ll> ord_dep(N);
    for(int i = 0; i < N; i++) ord_dep[hld.subtree(i+1).fi] = dep[i];
    seg = segtree(ord_dep);
}

ll Query(int S, int X[], int T, int Y[]) {
    for(int i = 0; i < T; i++) {
        vector<pii> path = hld.path(1, Y[i]+1);
        for(auto j : path) seg.update(j.fi, j.se, dep[Y[i]]);
    }
    ll ans = LLINF;
    for(int i = 0; i < S; i++) {
        vector<pii> path = hld.path(1, X[i]+1);
        for(auto j : path) ans = min(ans, seg.query(j.fi, j.se)+dep[X[i]]);
    }
    seg.clear();
    return ans;
}
