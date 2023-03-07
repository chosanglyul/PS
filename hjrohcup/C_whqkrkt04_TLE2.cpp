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

bool cmp(pll a, pll b, pll x, pll y) {
    if(a.se >= 0 || b.se >= 0) return false;
    if(a.fi*b.fi <= 0LL) return !a.fi && !b.fi;
    return x == y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll x, y; cin >> x >> y;
    int n; cin >> n;
    vector<pll> A(n), B(n);
    for(int i = 0; i < n; i++) {
        cin >> A[i].fi >> A[i].se;
        A[i].fi -= x, A[i].se -= y;
        B[i] = {A[i].fi*A[i].fi, A[i].se};
        ll g = __gcd(B[i].fi, B[i].se);
        B[i] = {B[i].fi/g, B[i].se/g};
    }
    vector<int> cnt(n, 1);
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(cmp(A[i], A[j], B[i], B[j]))
                cnt[i]++, cnt[j]++;
    cout << *max_element(cnt.begin(), cnt.end()) << "\n";
    return 0;
}