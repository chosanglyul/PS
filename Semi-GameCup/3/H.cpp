#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
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
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x, y; cin >> n >> x >> y;
    long double q = (long double)x/y;
    ll a = 0LL, b = 0LL;
    vector<pll> A(n);
    for(int i = 0; i < n; i++) A[i].fi = i;
    for(auto &i : A) { cin >> i.se.fi; a += i.se.fi; }
    for(auto &i : A) { cin >> i.se.se; b += i.se.se; }
    sort(A.begin(), A.end(), [&](pll& x, pll& y) {
        if(x.se.se*y.se.fi == y.se.se*x.se.fi) return x.fi > y.fi;
        return x.se.se*y.se.fi < y.se.se*x.se.fi;
    });
    vector<long double> B(n, 0.0f);
    for(auto &i : A) {
        long double tmp = (long double)i.se.se/b;
        if(q >= tmp) {
            q -= tmp;
            B[i.fi] = 1.0f;
        } else {
            B[i.fi] = q/tmp;
            break;
        }
    }
    cout << fixed << setprecision(6);
    for(auto &i : B) cout << i << "\n";
    return 0;
}