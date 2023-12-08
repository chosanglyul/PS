#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    for(int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << endl;
        int n; cin >> n;
        vector<ll> A(n);
        for(auto &i : A) cin >> i;
        vector<vector<ll>> dp(n, vector<ll>(n, 0LL));
        vector<vector<ll>> L(n, vector<ll>(n, 0LL));
        vector<vector<ll>> R(n, vector<ll>(n, 0LL));
        vector<vector<int>> K(n, vector<int>(n));
        for(int i = 0; i < n; i++) {
            dp[i][i] = L[i][i] = R[i][i] = A[i];
            K[i][i] = i;
        }
        for(int i = 1; i < n; i++) {
            for(int j = 0; j+i < n; j++) {
                // dp[j][j+i]
                int k = max(j+1, K[j][j+i-1]);
                int kk = min(j+i, K[j+1][j+i]);
                while(k < kk && dp[j][k-1] <= dp[k+1][j+i]) k++;
                K[j][j+i] = k;
                L[j][j+i] = max(L[j][j+i-1], dp[j][j+i-1]+A[j+i]);
                R[j][j+i] = max(R[j+1][j+i], dp[j+1][j+i]+A[j]);
                dp[j][j+i] = max(L[j][k-1], R[k][j+i]);
            }
        }
        cout << dp[0][n-1] << endl;
    }
    return 0;
}
