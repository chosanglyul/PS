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
const int P = 998244353;
const ll LLINF = (ll)1e18+1;
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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
    int n; cin >> n;
    ll p, q; cin >> p >> q;
    ll ans = 0LL, r = mod(p*inv(q, P), P);
    for(int i = 0; i < (1<<n); i++) {
        int cnt = 0;
        for(int j = 0; j < n; j++) if(i&(1<<j)) cnt++;
        if(cnt < (n+1)/2) continue;
        ll prob = (i&1) ? r : 1LL-r;
        for(int j = 1; j < n; j++) {
            bool s = i&(1<<(j-1)), e = i&(1<<j);
            if(s == e) prob = mod(prob*r, P);
            else prob = mod(prob*(1LL-r), P);
        }
        ans = mod(ans+prob, P);
    }
    cout << ans << '\n';
    return 0;
}