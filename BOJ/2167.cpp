#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m)), B(n+1, vector<int>(m+1, 0));
    for(auto &i : A) for(auto &j : i) cin >> j;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            B[i][j] = B[i-1][j]+B[i][j-1]-B[i-1][j-1]+A[i-1][j-1];
    int q; cin >> q;
    while(q--) {
        int i, j, x, y; cin >> i >> j >> x >> y; --i, --j;
        cout << B[x][y]-B[i][y]-B[x][j]+B[i][j] << "\n";
    }
    return 0;
}