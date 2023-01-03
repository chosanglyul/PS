#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    int sx = 0, ex = n, sy = 0, ey = m;
    int q; cin >> q;
    while(q--) {
        int x, y, t; cin >> x >> y >> t; --x, --y;
        switch(t) {
            case 1: sy = y, ey = y+1, sx = max(sx, x+1); break;
            case 2: sy = y, ey = y+1, ex = min(ex, x); break;
            case 3: sx = x, ex = x+1, ey = min(ey, y); break;
            case 4: sx = x, ex = x+1, sy = max(sy, y+1); break;
            case 5: sx = max(sx, x+1), sy = max(sy, y+1); break;
            case 6: ex = min(ex, x), sy = max(sy, y+1); break;
            case 7: sx = max(sx, x+1), ey = min(ey, y); break;
            case 8: ex = min(ex, x), ey = min(ey, y); break;
            case 9: sy = y, ey = y+1, sx = x, ex = x+1; break;
        }
    }
    cout << (ll)(ey-sy)*(ex-sx) << "\n";
    return 0;
}