#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<pi, int> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 998244353;
const ll LLINF = 1e18+1;
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
    int n; cin >> n;
    vector<pii> A(n);
    vector<int> B, C(n), D(n+1, 0);
    for(auto &i : A) {
        cin >> i.fi.fi >> i.fi.se >> i.se;
        B.push_back(i.fi.fi);
    }
    for(int i = 0; i < n; i++) {
        int idx = lower_bound(B.begin(), B.end(), A[i].fi.se) - B.begin();
        C[i] = mod(mod(D[i]-D[idx], P)+mod(A[i].fi.fi-A[i].fi.se, P), P);
        D[i+1] = mod(D[i]+C[i], P);
    }
    int ans = (A.back().fi.fi+1)%P;
    for(int i = 0; i < n; i++) {
        if(A[i].se) ans = mod(ans+C[i], P);
    }
    cout << ans << "\n";
    return 0;
}