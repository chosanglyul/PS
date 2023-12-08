#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second

const int MAX_N = 1000 + 1;
const int MAX_K = 5000 + 1;

ll arr[MAX_N][MAX_N];
ll dp[MAX_N][MAX_N];
ll dp2[MAX_N][MAX_K];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) cin >> arr[i][j];
        for (int j=n; j>=3; --j) arr[i][j] += arr[i][j-1] + arr[i][j-2];
    }

    for (int r=1; r<=n; ++r) {
        memset(dp[0], 0, sizeof dp[0]);
        for (int i=1; i<=n/3; ++i) {
            dp[i][0] = 0;
            for (int j=3*i; j<=n; ++j) {
                dp[i][j] = max(dp[i][j-1], arr[r][j] + dp[i-1][j-3]);
            }
        }

        // invariant: dp2 is convoluted by row [0, r-1]
        int p1 = 0, p2 = 0;
        for (int i=1; i<=min(k, n/3*r); ++i) {
            if (p1 >= n/3 || dp[p1+1][n]-dp[p1][n] < dp2[r-1][p2+1]-dp2[r-1][p2]) {
                dp2[r][i] = dp2[r][i-1] + dp2[r-1][p2+1]-dp2[r-1][p2];
                p2++;
            } else {
                dp2[r][i] = dp2[r][i-1] + dp[p1+1][n]-dp[p1][n];
                p1++;
            }
        }
    }
    
    ll ans = 0;
    for (int i=0; i<=k; ++i) ans = max(ans, dp2[n][i]);
    cout << ans;

    return 0;
}