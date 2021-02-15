#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[5050505], A[5050505];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> A[i];
        sum += A[i];
    }
    for(int i = 1; i < n-1; i++)
        dp[i] = A[i]+min(0LL, dp[i-1]);
    ll mi = 0;
    for(int i = 1; i < n-1; i++)
        mi = min(dp[i], mi);
    cout << sum - mi << "\n";
    return 0;
}