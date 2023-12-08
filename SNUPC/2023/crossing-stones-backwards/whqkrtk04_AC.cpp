#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll P = 1'000'000'007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<ll>> dp(n, vector<ll>(m, 0LL)); dp[0][0] = 1LL;
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < min(i, m); j++) {
            for(int k = 0; k < m; k++)
                dp[i][j] += dp[i-j-1][k]*min(k+1, m-j);
            dp[i][j] %= P;
        }
    }
    ll ans = 0LL;
    for(auto i : dp.back()) ans += i;
    cout << ans%P << "\n";
    return 0;
}
