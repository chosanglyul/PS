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
    const int N = 1e6+1e5;
    int n, k; ll m; cin >> n >> m >> k;
    vector<ll> A(N, 0LL);
    for(int i = 0; i <= n; i++) cin >> A[i];
    vector<pll> B(N, {0LL, 0LL});
    for(int i = 0; i+1 < N; i++) {
        B[i].fi += A[i];
        B[i+1].fi += B[i].fi/k;
        B[i+1].se += B[i].fi/k;
        B[i].fi %= k;
    }

    string s;
    for(int i = N-1; i > 0; i--) {
        s.push_back(B[i].fi/m+'0');
        ll tmp = min(B[i].fi%m, B[i].se);
        B[i-1].fi += tmp*k;
    }
    s.push_back(B[0].fi/m+'0');
    reverse(s.begin(), s.end());
    while(s.size() && s.back() == '0') s.pop_back();
    if(s.size()) {
        reverse(s.begin(), s.end());
        cout << s << "\n";
    } else cout << 0 << "\n";
    return 0;
}