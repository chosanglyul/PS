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

class segtree {
    private:
    int n;
    vector<int> seg;

    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = max(seg[i<<1], seg[i<<1|1]);
        }
    }

    void update(int i, int s, int e, int j, int x) {
        if(e <= j || s > j) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = max(seg[i<<1], seg[i<<1|1]);
        }
    }

    int query(int i, int s, int e, int l, int r) {
        if(e <= l || r <= s) return 0;
        if(l <= s && e <= r) return seg[i];
        return max(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(vector<int>& A) {
        n = A.size();
        seg = vector<int>(4*n, 0);
        init(1, 0, n, A);
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
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
    void link(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void init() {
        top[1] = 1;
        traverse1(1);
        traverse2(1);
    }
    pii subtree(int u) {
        return {in[u], in[u] + sz[u]};
    }
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
    HLD(int n) {
        adj.resize(n+1);
        in.resize(n+1);
        sz.resize(n+1);
        par.resize(n+1);
        top.resize(n+1);
        depth.resize(n+1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    HLD hld(n);
    vector<piii> E;
    for(int i = 1; i < n; i++) {
        int x, y, z; cin >> x >> y >> z;
        hld.link(x, y);
        E.push_back({z, {x, y}});
    }
    hld.init();
    vector<int> A(n, 0), Ind;
    for(auto &i : E) {
        int a = hld.subtree(i.se.fi).fi;
        int b = hld.subtree(i.se.se).fi;
        Ind.push_back(max(a, b));
        A[Ind.back()] = i.fi;
    }
    segtree S(A);
    int m; cin >> m;
    while(m--) {
        int t, x, y; cin >> t >> x >> y;
        if(t == 1) {
            S.update(Ind[--x], y);
        } else {
            vector<pii> path = hld.path(x, y);
            if(path.size()) path[path.size()-1].fi++;
            int ret = 0;
            for(auto i : path) ret = max(ret, S.query(i.fi, i.se));
            cout << ret << "\n";
        }
    }
    return 0;
}