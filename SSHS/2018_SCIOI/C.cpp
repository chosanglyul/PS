#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[2020][55];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    if((n*(n+1)/2)%2) {
        cout << "0\n";
        return 0;
    }
    dp[0][0] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i*(i+1)/2; j++) {
            dp[j+i+1][i+1] += dp[j][i];
            dp[j][i+1] += dp[j][i];
        }
    }
    cout << dp[n*(n+1)/4][n]/2 << "\n";
    return 0;
}