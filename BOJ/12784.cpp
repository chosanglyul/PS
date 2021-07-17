#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int dfs(int x, int p, vector<vector<pi>>& E) {
    int tmp = 0;
    bool end = true;
    for(auto &i : E[x]) {
        if(i.fi == p) continue;
        end = false;
        tmp += min(i.se, dfs(i.fi, x, E));
    }
    return (end ? INF : tmp);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<pi>> E(n);
        for(int i = 0; i < m; i++) {
            int x, y, z; cin >> x >> y >> z; --x, --y;
            E[x].push_back({y, z});
            E[y].push_back({x, z});
        }
        if(n == 1) cout << 0 << "\n";
        else cout << dfs(0, -1, E) << "\n";
    }
    return 0;
}