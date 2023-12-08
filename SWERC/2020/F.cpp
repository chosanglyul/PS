#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

const int MAX_N = 2021 + 2;

ll dp[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, r, m;
    cin >> r >> n >> m;

    dp[n][1] = 1;
    for (int i=n-1; i>=1; --i) {
        for (int j=1; j<=(n-i+2)/2; ++j) {
            if (i >= r) {
                dp[i][j] += dp[i+1][j] * j;
                dp[i][j] += dp[i+1][j-1] * (n-i-2*j+3);
            } else {
                dp[i][j] += dp[i+1][j] * (j-1);
                dp[i][j] += dp[i+1][j-1] * (n-i-2*j+3);
            }
            dp[i][j] %= m;
            // cout << i << ' ' << j << ' ' << dp[i][j] << endl;
        }
    }
    
    ll ans = accumulate(dp[1]+1, dp[1]+MAX_N, 0ll);
    cout << ans % m;

    return 0;
}