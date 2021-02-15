#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1e9+7;
const ll LLINF = 1e18+1;

int dp[505][505];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, x, y; cin >> n >> m >> x >> y;
    if(x > y) {
        swap(n, m);
        swap(x, y);
    }
    for(int i = 1; i <= n; i++) {
        dp[i][0] = INF;
        for(int j = 0; j <= i-1; j++)
            dp[i][0] = min(dp[i][0], max(dp[j][0], dp[i-1-j][0])+x);
    }
    for(int i = 1; i <= m; i++) {
        dp[0][i] = INF;
        for(int j = 0; j <= i-1; j++)
            dp[0][i] = min(dp[0][i], max(dp[0][j], dp[0][i-1-j])+y);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            dp[i][j] = min(dp[i-1][j]+x, dp[i][j-1]+y);
            int q = j;
            for(int p = 0; p <= i-1; p++) {
                while(q > 0 && dp[p][q] > dp[i-1-p][j-q]) {
                    dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-1-p][j-q])+x);
                    --q;
                }
                while(q < j && dp[p][q] < dp[i-1-p][j-q]) {
                    dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-1-p][j-q])+x);
                    ++q;
                }
            }
            q = j-1;
            for(int p = 0; p <= i; p++) {
                while(q > 0 && dp[p][q] > dp[i-p][j-1-q]) {
                    dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-p][j-1-q])+y);
                    --q;
                }
                while(q < j-1 && dp[p][q] < dp[i-p][j-1-q]) {
                    dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-p][j-1-q])+y);
                    ++q;
                }
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}