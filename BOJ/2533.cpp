#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<bool, bool> pb;
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

int dfs(int x, bool y, int p, vector<vector<int>>& E, vector<pi>& F, vector<pb>& vis) {
    if(E[x].size() == 1 && p >= 0) {
        return y ? 1 : 0;
    } else if(y) {
        if(vis[x].se) return F[x].se;
        vis[x].se = true;
        for(auto &i : E[x]) {
            if(i == p) continue;
            F[x].se += min(dfs(i, false, x, E, F, vis), dfs(i, true, x, E, F, vis));
        }
        return ++F[x].se;
    } else {
        if(vis[x].fi) return F[x].fi;
        vis[x].fi = true;
        for(auto &i : E[x]) {
            if(i == p) continue;
            F[x].fi += dfs(i, true, x, E, F, vis);
        }
        return F[x].fi;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> E(n);
    vector<pi> F(n, {0, 0});
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    vector<pb> vis(n, {false, false});
    cout << min(dfs(0, true, -1, E, F, vis), dfs(0, false, -1, E, F, vis)) << "\n";
    //cout << F;
    return 0;
}