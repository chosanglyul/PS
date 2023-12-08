#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<char>> A(n, vector<char>(m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> A[i][j];

    vector<vector<bool>> maskB(n, vector<bool>(m, true));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            maskB[i][j] = (A[i][j] != 'R');
            if(i > 0) maskB[i][j] = maskB[i][j] && maskB[i-1][j];
            if(j > 0) maskB[i][j] = maskB[i][j] && maskB[i][j-1];
        }
    }

    vector<vector<bool>> maskR(n, vector<bool>(m, true));
    for(int i = n-1; i >= 0; i--) {
        for(int j = m-1; j >= 0; j--) {
            maskR[i][j] = (A[i][j] != 'B');
            if(i < n-1) maskR[i][j] = maskR[i][j] && maskR[i+1][j];
            if(j < m-1) maskR[i][j] = maskR[i][j] && maskR[i][j+1];
        }
    }

    vector<vector<ll>> dp(n+1, vector<ll>(m+1, 0LL)); dp[0][m] = 1LL;
    for(int i = 1; i <= n; i++) {
        ll cnt = 0LL;
        for(int j = m; j >= 0; j--) {
            cnt += dp[i-1][j];
            if((j == 0 || maskB[i-1][j-1]) && (j == m || maskR[i-1][j]))
                dp[i][j] = cnt;
        }
    }

    ll ans = 0LL;
    for(int i = 0; i <= m; i++) ans += dp[n][i];
    cout << ans << "\n";
    return 0;
}