#include <bits/stdc++.h>
using namespace std;

int dfs(int x, vector<int>& A, vector<vector<int>>& E, vector<bool>& vis) {
    if(vis[x]) return 0;
    vis[x] = true;
    for(auto i : E[x]) {
        if(A[i] == -1 || dfs(A[i], A, E, vis)) {
            A[i] = x;
            return 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> E(n);
    vector<int> A(m, -1);
    for(auto &i : E) {
        int x; cin >> x;
        i.resize(x);
        for(auto &j : i) {
            cin >> j;
            j--;
        }
    }
    int cnt = 0;
    for(int i = 0; i < E.size(); i++) {
        vector<bool> vis(E.size(), false);
        cnt += dfs(i, A, E, vis);
    }
    for(int i = 0; i < E.size(); i++) {
        vector<bool> vis(E.size(), false);
        if(dfs(i, A, E, vis)) cnt++, k--;
        if(k == 0) break;
    }
    cout << cnt << "\n";
    return 0;
}