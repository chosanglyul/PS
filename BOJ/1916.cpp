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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<pii>> E(n);
    for(int i = 0; i < m; i++) {
        int x, y, z; cin >> x >> y >> z; --x, --y;
        E[x].push_back({y, z});
    }
    int s, e; cin >> s >> e; --s, --e;
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    Q.push({0, s});
    vector<int> D(n, INF); D[s] = 0;
    while(Q.size()) {
        auto [val, hre] = Q.top(); Q.pop();
        if(val > D[hre]) continue;
        for(auto [nxt, cst] : E[hre]) {
            if(val+cst >= D[nxt]) continue;
            D[nxt] = val+cst;
            Q.push({val+cst, nxt});
        }
    }
    cout << D[e] << "\n";
    return 0;
}