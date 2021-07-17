#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll a, b, c; cin >> a >> b >> c;
    ll ans = 1;
    while(b) {
        if(b&1) ans = (ans*a)%c;
        a = (a*a)%c;
        b >>= 1;
    }
    cout << ans << "\n";
    return 0;
}