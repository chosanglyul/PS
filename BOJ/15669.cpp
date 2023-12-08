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
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
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

void dfs1(int x, int p, vector<bool> &vis, vector<vector<int>> &E, vector<vector<pii>> &Edp, vector<pii> &Vdp) {
    if(vis[x]) return;
    vis[x] = true;
    for(int i = 0; i < E[x].size(); i++) {
        if(E[x][i] == p) continue;
        dfs1(E[x][i], x, vis, E, Edp, Vdp);
        Edp[x][i] = Vdp[E[x][i]];
        swap(Edp[x][i].fi, Edp[x][i].se);
        Edp[x][i].fi++;
        Vdp[x].fi += Edp[x][i].fi;
        Vdp[x].se += Edp[x][i].se;
    }
}

void dfs2(int x, int p, vector<bool> &vis, vector<vector<int>> &E, vector<vector<pii>> &Edp, vector<pii> &Vdp) {
    if(vis[x]) return;
    vis[x] = true;
    for(int i = 0; i < E[x].size(); i++) {
        if(E[x][i] == p) {
            Edp[x][i].fi = Vdp[p].se-Vdp[x].fi+1;
            Edp[x][i].se = Vdp[p].fi-Vdp[x].se-1;
            Vdp[x].fi += Edp[x][i].fi;
            Vdp[x].se += Edp[x][i].se;
        }
    }
    for(int i = 0; i < E[x].size(); i++) {
        if(E[x][i] != p) {
            dfs2(E[x][i], x, vis, E, Edp, Vdp);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> E(n);
    vector<vector<pii>> Edp(n);
    vector<pii> Vdp(n, {0, 0});
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v; --u, --v;
        E[u].push_back(v); Edp[u].push_back({0, 0});
        E[v].push_back(u); Edp[v].push_back({0, 0});
    }
    for(auto &i : E) sort(i.begin(), i.end());
    vector<bool> vis(n, false);
    dfs1(0, -1, vis, E, Edp, Vdp);
    fill(vis.begin(), vis.end(), false);
    dfs2(0, -1, vis, E, Edp, Vdp);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; --u, --v;
        int c; cin >> c;
        int idx = lower_bound(E[u].begin(), E[u].end(), v) - E[u].begin();
        int jdx = lower_bound(E[v].begin(), E[v].end(), u) - E[v].begin();
        if(!c) cout << (ll)Edp[u][idx].fi*Edp[v][jdx].se+(ll)Edp[u][idx].se*Edp[v][jdx].fi << "\n";
        else cout << (ll)Edp[u][idx].fi*Edp[v][jdx].fi+(ll)Edp[u][idx].se*Edp[v][jdx].se << "\n";
    }
    return 0;
}
