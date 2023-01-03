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

void dfs(int x, int d, vector<vector<int>>& E, vector<bool>& chk, vector<bool>& col) {
    if(chk[x]) return;
    chk[x] = true;
    if(d%2 == 1) col[x] = true;
    else col[x] = false;
    for(auto i : E[x]) dfs(i, d+1, E, chk, col);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> E(n);
        vector<pii> EE;
        vector<bool> chk(n, false), col(n, false);
        for(int i = 0; i < m; i++) {
            int x, y; cin >> x >> y; --x, --y;
            EE.push_back({x, y});
            E[x].push_back(y);
            E[y].push_back(x);
        }
        for(int i = 0; i < n; i++) dfs(i, 0, E, chk, col);
        bool can = true;
        for(auto e : EE) if(col[e.fi] == col[e.se]) can = false;
        if(can) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}