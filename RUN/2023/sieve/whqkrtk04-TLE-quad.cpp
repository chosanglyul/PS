#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> D(n);
    for(int i = 1; i <= n; i++) {
        auto &T = D[i-1];
        for(int j = 1; j < i; j++)
            if(i%j == 0) T.push_back(j);
    }
    vector<ll> A(n), B(n);
    for(auto &i : A) cin >> i;
    ll ans = 0LL;
    for(int i = 1; i <= n; i++) {
        ll tmp = 0LL;
        for(auto j : D[i-1]) tmp += B[j-1];
        B[i-1] = A[i-1]-tmp;
        ans += abs(B[i-1]);
    }
    cout << ans << "\n";
    return 0;
}
