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

typedef struct edge {
    int nxt, idx, val;
    edge(int nxt, int idx, int val) : nxt(nxt), idx(idx), val(val) {}
} edge;
ostream& operator<<(ostream& os, const edge& i) { os << i.nxt << " " << i.idx << " " << i.val << "  "; os << "\n"; return os; }

bool dfs(int x, vector<vector<edge>> &E, vector<bool> &vis, vector<int> &ans, edge &e) {
    if(x < 0 || vis[x]) return true;
    vis[x] = true;
    for(auto &i : E[x]) {
        if(ans[i.idx] == 1-i.val) continue;
        ans[i.idx] = i.val;
        if(dfs(i.nxt, E, vis, ans, i)) return true;
    }
    if(e.idx >= 0) ans[e.idx] = 1-e.val;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<edge>> E(m);
    vector<pii> C(n, {-1, -1}), D(n, {-1, -1});
    for(int i = 0; i < m; i++) {
        int t; cin >> t;
        for(int j = 0; j < t; j++) {
            int x; cin >> x;
            int idx = abs(x)-1;
            edge e(-1, idx, x > 0);
            if(x < 0) {
                C[idx] = {i, j};
                if(D[idx].fi != -1) {
                    E[D[idx].fi][D[idx].se].nxt = i;
                    e.nxt = D[idx].fi;
                }
            } else {
                D[idx] = {i, j};
                if(C[idx].fi != -1) {
                    E[C[idx].fi][C[idx].se].nxt = i;
                    e.nxt = C[idx].fi;
                }
            }
            E[i].push_back(e);
        }
    }
    //cout << " " << E;

    vector<int> ans(n, -1);
    vector<bool> vis(n, false);
    edge e(-1, -1, -1);
    for(int i = 0; i < m; i++) {
        if(!dfs(i, E, vis, ans, e)) {
            cout << -1 << "\n";
            return 0;
        }
    }
    for(auto &i : ans) if(i == -1) i = 0;
    cout << ans;
    return 0;
}