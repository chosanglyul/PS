#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101010;

int n, q;
vector<int> g[MAXN];

int par[MAXN], sub[MAXN];
void dfs(int p, int v) {
    sub[v] = 1;
    for (int x : g[v]) if (p != x) {
        par[x] = v;
        dfs(v, x);
        sub[v] += sub[x];
    }
    if (p != -1) 
        g[v].erase(find(g[v].begin(), g[v].end(), p));

    for (int i = 1; i < g[v].size(); i++) {
        if (sub[g[v][i]] > sub[g[v][0]])
            swap(g[v][i], g[v][0]);
    }
}
int dn, ln[MAXN], inv[MAXN], top[MAXN], depth[MAXN], heavy[MAXN];
void get_hld(int v) {
    ln[v] = ++dn;
    inv[dn] = v;
    if (!g[v].empty()) heavy[v] = g[v][0];
    for (int x : g[v]) {
        if (x == g[v][0]) {
            top[x] = top[v];
        }
        else {
            top[x] = x;
        }
        depth[x] = depth[v] + 1;
        get_hld(x);
    }
}

int sp[20][MAXN];

const int INF = 1e9 + 10;
struct seg {
    long long tree[4 * MAXN];
    int cnt[4 * MAXN];
    void init(int l, int r, int x) {
        if (l == r) {
            tree[x] = INF;
            cnt[x] = 1;
            return;
        }
        int m = (l + r) / 2;
        init(l, m, 2 * x);
        init(m + 1, r, 2 * x + 1);
        tree[x] = min(tree[2 * x], tree[2 * x + 1]);
        cnt[x] = cnt[2 * x] + cnt[2 * x + 1];
    }
    void update(int a, long long v, int l, int r, int x) {
        if (l == r) {
            tree[x] = v;
            cnt[x] = 0;
            return;
        }
        int m = (l + r) / 2;
        if (a <= m) 
            update(a, v, l, m, 2 * x);
        else
            update(a, v, m + 1, r, 2 * x + 1);
        tree[x] = min(tree[2 * x], tree[2 * x + 1]);
        cnt[x] = cnt[2 * x] + cnt[2 * x + 1];
    }
    long long get(int a, int b, int l, int r, int x) {
        if (b < l || a > r) return 0;
        if (a <= l && r <= b) return cnt[x];
        int m = (l + r) / 2;
        return get(a, b, l, m, 2 * x) + get(a, b, m + 1, r, 2 * x + 1);
    }
    void query(int a, int b, long long v, int l, int r, int x, vector<int> &vec) {
        if (b < l || a > r) return;
        if (l == r) {
            vec.push_back(l);
            tree[x] = INF;
            cnt[x] = 1;
            return;
        }
        int m = (l + r) / 2;
        if (tree[2 * x] <= v) 
            query(a, b, v, l, m, 2 * x, vec);
        if (tree[2 * x + 1] <= v)
            query(a, b, v, m + 1, r, 2 * x + 1, vec);

        tree[x] = min(tree[2 * x], tree[2 * x + 1]);
        cnt[x] = cnt[2 * x] + cnt[2 * x + 1];
    }
} t1;

struct fenwick {
    long long tree[MAXN];
    void update(int a, int b, int v) {
        for (; a < MAXN; a += a & -a) tree[a] += v;
        for (++b; b < MAXN; b += b & -b) tree[b] -= v;
    }
    long long query(int a) {
        long long r = 0;
        for (; a > 0; a -= a & -a) r += tree[a];
        return r;
    }
} t2;
int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    int D = depth[v] - depth[u];
    for (int i = 0; i < 20; i++) {
        if (D >> i & 1) v = sp[i][v];
    }
    for (int i = 19; i >= 0; i--) {
        if (sp[i][v] != sp[i][u]) {
            u = sp[i][u];
            v = sp[i][v];
        }
    }
    return (u == v) ? u : par[u];
}
long long mx[MAXN];
bool used[MAXN];
int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(-1, 1);
    top[1] = 1;
    get_hld(1);
    for (int i = 1; i <= n; i++) sp[0][i] = par[i];
    for (int j = 1; j < 20; j++)
        for (int i = 1; i <= n; i++)
            sp[j][i] = sp[j - 1][sp[j - 1][i]];
        
    for (int i = 1; i <= n; i++) if (!g[i].empty()) used[i] = true;
    long long ans = 0;
    long long tot = 0;

    t1.init(1, n, 1);
    while (q--) {
        int u, v, x;
        cin >> u >> v >> x;
        int r = lca(u, v);
        tot += (long long)x * (depth[u] + depth[v] - 2 * depth[r]);
        for (int ppu : {u, v}) {
            vector<int> upd;
            int heavy_cnt = 0;
            int pu = ppu;
            while (1) {
                // process H -> L instances
                if (max(ln[r], ln[top[pu]]) <= ln[par[pu]]) {
                    heavy_cnt += t1.get(max(ln[r], ln[top[pu]]), ln[par[pu]], 1, n, 1);
                    t1.query(max(ln[r], ln[top[pu]]), ln[par[pu]], x, 1, n, 1, upd);
                }
                if (top[pu] == top[r]) break;
                // process L -> H instance
                pu = top[pu];
                long long val = t2.query(ln[pu]);
                if (pu != 1) {
                    long long hval = t2.query(ln[heavy[par[pu]]]);
                    if (used[par[pu]]) ans -= hval;
                    else ans -= mx[par[pu]];
                    mx[par[pu]] = max(mx[par[pu]], val + x);
                    if (mx[par[pu]] > hval) {
                        t1.update(ln[par[pu]], mx[par[pu]] - hval, 1, n, 1);
                        used[par[pu]] = false;
                    }
                    if (used[par[pu]]) ans += hval;
                    else ans += mx[par[pu]];       
                }
                pu = par[pu];
            }
            pu = ppu;
            while (1) {
                t2.update(max(ln[r] + 1, ln[top[pu]]), ln[pu], x);
                if (top[pu] == top[r]) break;
                pu = par[top[pu]];
            }
            ans += (long long)x * heavy_cnt;
            for (int x : upd) {
                ans -= mx[inv[x]];
                ans += t2.query(ln[heavy[inv[x]]]);
                used[inv[x]] = true;
            }
            upd.clear();
        }
        cout << tot - ans << '\n';
    }

}