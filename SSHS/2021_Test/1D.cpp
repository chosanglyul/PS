#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solve(ll n, ll k) {
    if(n == 1LL) return 1LL;
    else if(k-(n>>1) <= 0) return (k<<1)-1;
    else return solve(n>>1, k-(n>>1))<<1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, k; cin >> n >> k;
    ll tmp = 1LL;
    while(tmp < n) tmp <<= 1;
    ll ans = solve(tmp, k+tmp-n);
    if(ans <= (tmp-n)<<1) ans = (ans>>1)-tmp+(n<<1);
    else ans -= (tmp-n)<<1;
    cout << ans << "\n";
    return 0;
}