#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

pi dfs(int x, int d, vector<vector<pi>>& E, vector<bool> vis) {
    if(vis[x]) return {-1, -1};
    vis[x] = true;
    pi ret = {d, x};
    for(auto &i : E[x]) ret = max(ret, dfs(i.fi, d+i.se, E, vis));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<vector<pi>> E(n);
    for(int i = 0; i < n; i++) {
        int j; cin >> j; j--;
        while(true) {
            int x, y; cin >> x;
            if(x == -1) break;
            cin >> y; x--;
            E[j].emplace_back(x, y);
        }
    }
    vector<bool> vis(n, false);
    int x = dfs(0, 0, E, vis).se;
    vis = vector<bool>(n, false);
    cout << dfs(x, 0, E, vis).fi << "\n";
    return 0;
}