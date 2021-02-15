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

vector<int> bfs(vector<vector<int>>& E) {
    queue<pi> Q;
    Q.push({0, 0});
    vector<bool> visit(E.size(), false);
    vector<int> D(E.size());
    while(Q.size()) {
        pi x = Q.front();
        Q.pop();
        if(visit[x.fi]) continue;
        visit[x.fi] = true;
        D[x.fi] = x.se;
        for(auto i : E[x.fi])
            Q.push({i, x.se+1});
    }
    return D;
}

int dfs(int x, vector<vector<int>>& E, vector<bool>& visit, vector<int>& D, vector<int>& R) {
    if(visit[x]) return R[x];
    visit[x] = true;
    for(auto i : E[x]) {
        if(D[x] < D[i]) R[x] = min(R[x], dfs(i, E, visit, D, R));
    }
    return R[x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> E(n, vector<int>());
        for(int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            E[--u].push_back(--v);
        }
        vector<int> D = bfs(E);
        vector<int> R(D);
        for(int i = 0; i < n; i++) {
            for(auto j : E[i])
                R[i] = min(D[j], R[i]);
        }
        vector<bool> visit(n, false);
        for(int i = 0; i < n; i++)
            dfs(i, E, visit, D, R);
        for(auto i : R) cout << i << " ";
        cout << "\n";
    }
    return 0;
}