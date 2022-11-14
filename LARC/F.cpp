#include <bits/stdc++.h>
using namespace std;

void dfs(int x, vector<vector<int>>& E, vector<bool>& chk) {
    if(chk[x]) return;
    chk[x] = true;
    for(auto i : E[x]) dfs(i, E, chk);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> E(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; --u, --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    vector<bool> chk(n, false);
    chk[n-1] = true;
    dfs(n-2, E, chk);
    chk[n-1] = false;
    for(int i = 0; i < n; i++) {
        if(!chk[i]) cout << 'A';
        else cout << 'B';
    }
    cout << '\n';
    return 0;
}