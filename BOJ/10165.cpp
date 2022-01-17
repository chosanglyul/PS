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
    int n, m; cin >> n >> m;
    vector<pii> A(m);
    for(int i = 0; i < m; i++) {
        A[i].fi = i;
        cin >> A[i].se.fi >> A[i].se.se;
        if(A[i].se.fi > A[i].se.se) A[i].se.se += n;
    }
    sort(A.begin(), A.end(), [&](pii a, pii b) {
        if(a.se.fi == b.se.fi) return a.se.se > b.se.se;
        return a.se.fi < b.se.fi;
    });
    vector<bool> ans(m, true);
    int ma = -1;
    for(int i = 0; i < m; i++) {
        if(A[i].se.se <= ma) ans[A[i].fi] = false;
        ma = max(ma, A[i].se.se);
    }
    ma -= n;
    for(int i = 0; i < m; i++)
        if(A[i].se.se <= ma)
            ans[A[i].fi] = false;
    for(int i = 0; i < m; i++)
        if(ans[i]) cout << i+1 << " ";
    cout << "\n";
    return 0;
}