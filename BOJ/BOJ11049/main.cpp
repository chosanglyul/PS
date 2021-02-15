#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

int dp[505][505];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> A(n+1);
    for(int i = 0; i < n; i++) cin >> A[i] >> A[n];
    for(int i = 0; i < n; i++) dp[i][i+1] = 0;
    for(int i = 2; i <= n; i++) {
        for(int j = 0; j <= n-i; j++) {
            dp[j][j+i] = INT_MAX;
            for(int k = j+1; k < j+i; k++) dp[j][j+i] = min(dp[j][j+i], dp[j][k]+dp[k][j+i]+A[j]*A[k]*A[j+i]);
        }
    }
    cout << dp[0][n] << "\n";
    return 0;
}