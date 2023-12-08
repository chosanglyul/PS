#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n; cin >> n;
    ll ans = 0LL;
    for(ll i = 1LL; i <= (ll)1e6; i++) {
        string s = to_string(i);
        string a = s, b = s, t = s; t.pop_back();
        reverse(s.begin(), s.end());
        reverse(t.begin(), t.end());
        a += s, b += t;
        ll x = stoll(a), y = stoll(b);
        if(x <= n) ans++;
        if(y <= n) ans++;
    }
    cout << ans << "\n";
    return 0;
}