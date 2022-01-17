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

ll calc(vector<pll>& B, int s, int e) {
    ll tmp = (s ? B[e].se.fi-B[s-1].se.fi : B[e].se.fi);
    tmp -= (B[e].fi-1)*B[e].se.se;
    return tmp;
}

ll solve(int l, int r, vector<pll>& B) {
    int s = l, e = r, n = B.size();
    while(l+3 < r) {
        int mi = l+r>>1;
        ll x = calc(B, s, mi), y = calc(B, mi, e);
        if(x == y) return max(x, y);
        if(x < y) l = mi+1;
        else r = mi-1;
    }
    ll ans = LLINF;
    for(int i = max(0, l); i <= min(r, n-1); i++) {
        ll tmp = max(calc(B, s, i), calc(B, i, e));
        ans = min(ans, tmp);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t; cin >> n >> t;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    vector<pll> B(n);
    for(int i = n-1, j = 1; i >= 0; i--, j++) {
        B[i].fi = j;
        if(i && A[i] < A[i-1]) j = 0;
    }
    B[0].se = {B[0].fi, 1};
    for(int i = 1, j = 2; i < n; i++, j++) {
        if(B[i-1].fi == 1) j = 1;
        B[i].se.fi = B[i-1].se.fi+B[i].fi;
        B[i].se.se = j;
    }
    for(auto i : B) cout << i << "    ";
    cout << "\n";
    while(t--) {
        int l, r; cin >> l >> r;
        cout << solve(--l, --r, B) << "\n";
    }
    return 0;
}