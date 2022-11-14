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
    int n; cin >> n;
    vector<pi> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    sort(A.begin(), A.end());
    vector<pi> B = { {A.front().se, A.front().se} }, C = { {A.back().se, A.back().se} };
    for(int i = 1; i < n; i++) B.emplace_back(max(B.back().fi, A[i].se), min(B.back().se, A[i].se));
    for(int i = n-2; i >= 0; i--) C.emplace_back(max(C.back().fi, A[i].se), min(C.back().se, A[i].se));
    reverse(C.begin(), C.end());
    int l = 0, r = 2*INF;
    while(l+1 < r) {
        int m = (int)(((ll)l+r)/2LL);
        bool can = false;
        for(int s = 0, e = 0; s < n && e < n; s++) {
            while(e < n && A[e].fi - A[s].fi < m) e++;
            if(s == 0 && e == n) {
                can = true;
                break;
            }
            int ma = -INF, mi = INF;
            if(s > 0) {
                ma = max(ma, B[s-1].fi);
                mi = min(mi, B[s-1].se);
            }
            if(e < n) {
                ma = max(ma, C[e].fi);
                mi = min(mi, C[e].se);
            }
            if(ma - mi < m) {
                can = true;
                break;
            }
        }
        if(can) r = m;
        else l = m;
    }
    cout << l/2 << "." << (l%2 ? "5" : "0") << "\n";
    return 0;
}