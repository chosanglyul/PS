#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

struct DisjointSet {
    int n, sz;
    vector<int> par;
    DisjointSet(int _n): n(_n) {
        sz = n;
        par.resize(n);
        iota(par.begin(), par.end(), 0);
    }

    int find(int x) {
        return par[x] = (x == par[x] ? x : find(par[x]));
    }

    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        par[u] = v;
        sz--;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> l(n+1);
    for (int i=1; i<=n; ++i) cin >> l[i];
    vector<int> lcpy(l.begin()+1, l.end());
    sort(lcpy.begin(), lcpy.end());
    lcpy.erase(unique(lcpy.begin(), lcpy.end()), lcpy.end());
    for (int i=1; i<=n; ++i) l[i] = lower_bound(lcpy.begin(), lcpy.end(), l[i]) - lcpy.begin();

    vector<pii> edges(m);
    for (auto&[x, y]: edges) cin >> x >> y;

    array<vector<pii>, 2> tl; // (node cnt, component cnt)
    tl[0] = tl[1] = vector<pii>(lcpy.size());
    for (int i=1; i<=n; ++i) tl[0][l[i]].first++;
    for (int i=1; i<lcpy.size(); ++i) tl[0][i].first += tl[0][i-1].first;
    for (int i=0; i<lcpy.size(); ++i) tl[1][i].first = n - tl[0][i].first;
    
    sort(edges.begin(), edges.end(), [&](pii a, pii b) {
        return max(l[a.first], l[a.second]) < max(l[b.first], l[b.second]);
    });

    int p = 0;
    DisjointSet dsu(n+1);
    for (int t=0; t<lcpy.size(); ++t) {
        while (p < edges.size() && max(l[edges[p].first], l[edges[p].second]) <= t) {
            dsu.merge(edges[p].first, edges[p].second);
            p++;
        }
        tl[0][t].second = dsu.sz - (n+1-tl[0][t].first);
    }

    sort(edges.begin(), edges.end(), [&](pii a, pii b) {
        return min(l[a.first], l[a.second]) > min(l[b.first], l[b.second]);
    });

    dsu = DisjointSet(n+1);
    p = 0;
    for (int t=(int)lcpy.size()-1; t>=0; --t) {
        while (p < edges.size() && min(l[edges[p].first], l[edges[p].second]) > t) {
            dsu.merge(edges[p].first, edges[p].second);
            p++;
        }
        tl[1][t].second = dsu.sz - (n+1-tl[1][t].first);
    }

    for (int i=0; i<lcpy.size(); ++i) {
        // cout << tl[0][i].first << ' ' << tl[0][i].second << ' ' << tl[1][i].first << ' ' << tl[1][i].second << '\n';
    }

    int ans = 0x3f3f3f3f;
    for (int t=0; t+1<lcpy.size(); ++t) {
        int comp_cnt = tl[0][t].second + tl[1][t].second;
        if (tl[0][t].first >= comp_cnt-1 && tl[1][t].first >= comp_cnt-1) {
            ans = min(ans, t);
        }
    }
    cout << (ans == 0x3f3f3f3f ? -1 : lcpy[ans]);

    return 0;
}