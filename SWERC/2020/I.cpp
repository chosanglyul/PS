#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

vector<int> bfs(int s, vector<vector<int>> &E) {
    int n = E.size();
    vector<int> D(n, INF); D[s] = 0;
    queue<pii> Q; Q.push({s, 0});
    vector<bool> vis(n, false); vis[s] = true;
    while(Q.size()) {
        pii tmp = Q.front(); Q.pop();
        for(auto i : E[tmp.fi]) {
            if(vis[i]) continue;
            vis[i] = true;
            D[i] = tmp.se+1;
            Q.push({i, D[i]});
        }
    }
    return D;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> E(n);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    vector<int> A = bfs(0, E);
    auto iter = max_element(A.begin(), A.end());
    if(*iter >= INF) {
        cout << -1 << "\n";
    } else {
        A = bfs(iter-A.begin(), E);
        iter = max_element(A.begin(), A.end());
        int tmp = *iter;
        int ans = 0;
        while ((1 << ans) < tmp) ans++;
        cout << ans << "\n";
    }
    return 0;
}