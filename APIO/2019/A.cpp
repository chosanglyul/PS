#include <bits/stdc++.h>
using namespace std;
typedef __int128_t ll;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; long long a, b; cin >> n >> a >> b;
    ll t = (ll)a*b/__gcd(a, b+1);
    vector<pll> A;
    for(int i = 0; i < n; i++) {
        long long x, y; cin >> x >> y; y++;
        if(y-x >= t) {
            A.push_back({0, t});
        } else {
            x %= t, y %= t;
            if(y < x) {
                A.push_back({x, t});
                A.push_back({0, y});
            } else A.push_back({x, y});
        }
    }
    sort(A.begin(), A.end());
    vector<pll> B;
    for(int i = 0; i < A.size(); i++) {
        if(B.empty() || A[i].fi > B.back().se) B.push_back(A[i]);
        else B.back().se = max(B.back().se, A[i].se);
    }
    long long ans = 0LL;
    for(auto i : B) ans += i.se-i.fi;
    cout << ans << "\n";
    return 0;
}