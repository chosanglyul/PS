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

ll getma(ll k, ll a, ll b, ll c) {
    ll ans = min((k-1LL)*b, (k/2LL)*a+((k-1LL)/2LL)*c);
    if(k%2LL == 0LL) ans = min(ans, ((k-1LL)/2LL)*a+((k-1LL)/2LL)*c+b);
    return ans;
}
ll getmi(ll k, ll a, ll b, ll c) {
    ll ans = max((k-1LL)*b, ((k-1LL)/2LL)*a+(k/2LL)*c);
    if(k%2LL == 0LL) ans = max(ans, ((k-1LL)/2LL)*a+((k-1LL)/2LL)*c+b);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        ll a, b, c, n, k; cin >> a >> b >> c >> n >> k;
        if(a < c) swap(a, c);
        if(a >= b && b >= c) {
            cout << getmi(k, a, b, c)+(n-k)*a << " ";
            cout << (k-1LL)*c+getma(n-k+1LL, a, b, c) << "\n";
        } else if(b >= a) {
            cout << (n-1LL)*b << " ";
            cout << (k-1LL)*c+getma(n-k+1LL, a, b, c) << "\n";
        } else {
            cout << getmi(k, a, b, c)+(n-k)*a << " ";
            cout << (n-1LL)*b << "\n";
        }
    }
    return 0;
}