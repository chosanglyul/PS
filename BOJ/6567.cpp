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
    while(true) {
        ll n, k; cin >> k >> n;
        if(n == 0) break;
        ll inv2 = inv(2LL, P), invn = inv(n, P);
        vector<ll> A(n+1LL, 1LL);
        for(int i = 1; i < A.size(); i++) A[i] = (A[i-1]*k)%P;
        ll ans = 0LL;
        if(n&1) ans = (ans+A[n+1>>1])%P;
        else ans = (ans+(A[n+2>>1]+A[n>>1])*inv2)%P;
        for(int i = 1; i <= n; i++) ans = (ans+A[__gcd((ll)i, n)]*invn)%P;
        cout << ans*inv2%P << "\n";
    }
    return 0;
}