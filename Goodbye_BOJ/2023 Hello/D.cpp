#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, P; cin >> n >> P;
    vector<ll> fib(n+1); fib[0] = 1LL; fib[1] = 2LL;
    for(int i = 2; i <= n; i++) fib[i] = (fib[i-1]+fib[i-2])%P;
    vector<vector<ll>> dp(n+1, vector<ll>(n+1, 0LL)); dp[0][0] = 1LL;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            for(int x = 1; x <= j; x++)
                for(int y = 0; y <= i-x; y++)
                    dp[i][j] = (dp[i][j]+((fib[x]*dp[y][x-1])%P)*dp[i-x-y][j-x])%P;

    ll ans = 0LL;
    for(int i = 1; i <= n; i++) ans = (ans+dp[n][i])%P;
    cout << ans << "\n";
    return 0;
}