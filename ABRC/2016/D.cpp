#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    ll g = a; x = 1, y = 0;
    if (b) g = ext_gcd(b, a%b, y, x), y -= a/b*x;
    return g;
}

void solve() {
    ll ax, ay, bx, by, k;
    cin >> ax >> ay >> bx >> by >> k;

    ll dx = bx-ax, dy = by-ay;
    ll g = __gcd(dx, dy);
    ll a = dx/g, b = dy/g;
    ll x0, y0;
    ext_gcd(b, -a, x0, y0);
    for (ll n=0; n<k; ++n) {
        ll x = x0 + n*a;
        ll y = y0 + n*b;
        ll cx = ax-x, cy = ay-y;
        cout << cx << ' ' << cy << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    while (cases--) solve();

    return 0;
}