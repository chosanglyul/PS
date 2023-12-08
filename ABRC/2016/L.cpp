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

void dfs(int x, pii y, vector<pii> &A, vector<bool> &vis, vector<vector<piii>> &E) {
    if(vis[x]) return;
    vis[x] = true;
    A[x] = y;
    for(auto &i : E[x]) {
        pii z = {y.fi+i.se.fi, y.se+i.se.se};
        dfs(i.fi, z, A, vis, E);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<piii>> E(n);
    for(int i = 0; i < m; i++) {
        pii a, b; cin >> a.fi >> a.se >> b.fi >> b.se;
        a.fi--, a.se--;
        E[a.fi].push_back({a.se, {b.fi, b.se}});
        E[a.se].push_back({a.fi, {-b.fi, -b.se}});
    }
    vector<bool> vis(n, false);
    vector<pii> A(n);
    for(int i = 0; i < n; i++)
        dfs(i, {0, 0}, A, vis, E);
    for(auto i : A) cout << i.fi << " " << i.se << "\n";
    return 0;
}