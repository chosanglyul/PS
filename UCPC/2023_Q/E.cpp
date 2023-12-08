#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int P = 998244353;
template <typename T>
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
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

ll gop2(ll x, ll y) { return mod(x*y, P); }
ll gop3(ll x, ll y, ll z) { return gop2(gop2(x, y), z); }
ll gop4(ll x, ll y, ll z, ll w) { return gop2(gop3(x, y, z), w); }

pll solve(ll n, ll m) {
    ll a = gop3(n, m, inv(2LL, P));
    ll b = gop4(n, m, m-1, inv(3LL, P));
    ll c = gop4(m, n, n-1, inv(3LL, P));
    ll d = gop2(gop4(n, n-1, m, m-1), inv(4LL, P));
    return {a, mod(a+b+c+d, P)};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> A(n), C(1, 0LL);
    for(auto &i : A) {
        cin >> i;
        C.push_back(mod(C.back()+i, P));
    }
    vector<pll> B(n);
    ll ans = 0LL, su = 0LL;
    for(int i = 0; i < n; i++) {
        B[i] = solve(A[i], C[n]-C[i+1]);
        su = mod(su+B[i].fi, P);
        ans = mod(ans+B[i].se-mod(B[i].fi*B[i].fi, P), P);
    }
    ans = mod(ans+mod(su*su, P), P);
    cout << ans << "\n";
    return 0;
}