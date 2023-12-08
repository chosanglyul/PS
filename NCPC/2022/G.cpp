#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 5000 + 1;

double dp[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<double> p(n);
    for (int i=0; i<n; ++i) cin >> p[i];
    sort(p.rbegin(), p.rend());

    for (int i=0; i<MAX_N; ++i) {
        for (int j=0; j<MAX_N; ++j) {
            dp[i][j] = 0.0;
        }
    }
    dp[0][0] = 1.0;

    for (int i=1; i<=n; ++i) {
        for (int j=0; j<=i; ++j) {
            if (j > 0) dp[i][j] += dp[i-1][j-1] * p[i-1];
            dp[i][j] += dp[i-1][j] * (1-p[i-1]);
        }
    }

    double ans = 0.0;
    for (int m=0; m<=n; ++m) {
        int c = (m+k+1) / 2;
        double tmp = 0.0;
        for (int i=c; i<=m; ++i) tmp += dp[m][i];
        ans = max(ans, tmp);
    }

    cout << fixed << setprecision(6) << ans;

    return 0;
}