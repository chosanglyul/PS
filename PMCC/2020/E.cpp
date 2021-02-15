#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const ll LLINF = 1e18+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll a = -LLINF, b = LLINF, c = -LLINF, d = LLINF, e = -LLINF;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        ll x, y, z; cin >> x >> y >> z;
        if(e != -LLINF) {
            if((e-x-y-z)%2) {
                cout << "NO\n";
                return 0;
            }
        } else e = x+y+z;
        a = max(a, x+y-z);
        b = min(b, x+y+z);
        c = max(c, y-x-z);
        d = min(d, y-x+z);
    }
    if(a > b || c > d) cout << "NO\n"; 
    else cout << (a-d)/2 << " " << (a+d)/2 << "\n";
    return 0;
}