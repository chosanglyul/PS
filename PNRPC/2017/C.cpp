#include <bits/stdc++.h>
using namespace std;
typedef __int128_t ll;

ll sum(ll n) {
    return n*(n+1) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    cin >> a >> b;
    ll ans = 0, cut = 1e6+1;
    for (ll k=1; k<cut; ++k) {
        ans += k * (b/k - (a-1)/k);
    }
    for (ll k=b/cut; k>=1; --k) {
        ll m = max(cut, max((a-1)/k, b/(k+1)) + 1);
        ll M = (k == 1 ? b : min(b/k, (a-1)/(k-1)));
        if (m <= M) ans += sum(M)-sum(m-1);
        // cout << k << ' ' << m << ' ' << M << endl;
    }
    cout << (long long)ans;

    return 0;
}