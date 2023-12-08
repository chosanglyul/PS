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

void dfs(int x, int p, vector<int> &V, vector<vector<int>> &E, vector<pii> &dp) {
    int cnt = (int)E[x].size()-1, a = 1, b = 1;
    for(auto i : E[x]) {
        if(i == p) continue;
        cnt -= V[i];
        dfs(i, x, V, E, dp);
        a += (V[i] ? dp[i].se : dp[i].fi);
        b += dp[i].se;
    }
    dp[x].fi = a;
    if(cnt >= 2) dp[x].se = a;
    else if(cnt == 1) dp[x].se = b;
    else dp[x].se = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> E(n);
    vector<int> V(n, 0);
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    for(int i = 0; i < m; i++) {
        int x; cin >> x; --x;
        V[x] = 1;
    }
    vector<pii> dp(n, {0, 0});
    dfs(0, -1, V, E, dp);
    cout << (V[0] ? dp[0].se : dp[0].fi) << "\n";
    return 0;
}