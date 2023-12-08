#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> A(n), B(n, 0LL);
    for(auto &i : A) cin >> i;
    ll ans = 0LL;
    for(int i = 1; i <= n; i++) {
        ll tmp = A[i-1]-B[i-1];
        for(int j = i; j <= n; j += i) B[j-1] += tmp;
        ans += abs(tmp);
    }
    cout << ans << "\n";
    return 0;
}
