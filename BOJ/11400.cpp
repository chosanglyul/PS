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

class BridgeGraph { // 0-based
private:
    vector<vector<int>> adj;
    vector<int> depth, highest;
public:
    BridgeGraph(int n) {
        adj.resize(n);
        depth.resize(n); highest.resize(n);
        fill(depth.begin() + 1, depth.end(), -1);
    }
    vector<pii> res;
    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
    void find_bridge(int u = 0, int p = -1) {
        for (int v: adj[u]) {
            if (v == p) continue;
            if (depth[v] == -1) {
                depth[v] = highest[v] = depth[u] + 1;
                find_bridge(v, u);
                if (depth[v] == highest[v]) res.emplace_back(u, v);
            }
            highest[u] = min(highest[u], highest[v]);
        }
    };
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int v, e; cin >> v >> e;
    BridgeGraph B(v);
    while(e--) {
        int x, y; cin >> x >> y;
        B.add_edge(--x, --y);
    }
    B.find_bridge();
    vector<pii> R = B.res;
    cout << R.size() << "\n";
    for(auto &i : R) if(i.fi > i.se) swap(i.fi, i.se);
    sort(R.begin(), R.end());
    for(auto i : R) cout << i.fi+1 << " " << i.se+1 << "\n";
    return 0;
}