#include <bits/stdc++.h>
using namespace std;

void dfs(int x, vector<vector<int>> &E, vector<bool> &vis) {
    if(vis[x]) return;
    vis[x] = true;
    for(auto i : E[x]) dfs(i, E, vis);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> E(2*n);

    bool ansmin = true;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        int u = abs(x)-1, v = abs(y)-1;
        if(x < 0) {
            if(y < 0) {
                ansmin = false;
                E[u].push_back(v+n);
                E[v].push_back(u+n);
            } else {
                E[u].push_back(v);
                E[v+n].push_back(u+n);
            }
        } else {
            if(y < 0) {
                E[u+n].push_back(v+n);
                E[v].push_back(u);
            } else {
                E[u+n].push_back(v);
                E[v+n].push_back(u);
            }
        }
    }

    if(ansmin) {
        cout << -1 << "\n";
        return 0;
    }

    vector<vector<bool>> vis(2*n, vector<bool>(2*n, false));
    for(int i = 0; i < 2*n; i++) dfs(i, E, vis[i]);

    for(int i = 0; i < n; i++) {
        if(vis[i+n][i] && vis[i][i+n]) {
            cout << 0 << "\n";
            return 0;
        }
    }

    for(int i = 0; i < n; i++) {
        if(vis[i][i+n]) {
            cout << 1 << "\n";
            return 0;
        }
    }

    cout << 2 << "\n";
    return 0;
}