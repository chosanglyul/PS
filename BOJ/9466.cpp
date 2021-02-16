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
const ll LLINF = 1e18+1;

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

bool dfs(int x, vector<vector<int>>& E, vector<bool>& vis, vector<bool>& can) {
    if(vis[x]) return can[x];
    vis[x] = true;
    bool c = false;
    for(auto &i : E[x]) c |= dfs(i, E, vis, can);
    return can[x] = c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<vector<int>> E(n);
        vector<bool> vis(n, false), can(n, true);
        for(int i = 0; i < n; i++) {
            int x; cin >> x; x--;
            E[x].push_back(i);
        }
        for(int i = 0; i < n; i++) {
            if(!vis[i]) dfs(i, E, vis, can);
        }
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(!can[i]) cnt++;
        }
        cout << cnt << "\n";
    }
    return 0;
}