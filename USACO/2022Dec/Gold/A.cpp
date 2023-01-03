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
    int n, a, b; cin >> n >> a >> b;
    vector<piii> A(n);
    for(int i = 0; i < n; i++) cin >> A[i].fi >> A[i].se.fi >> A[i].se.se;
    sort(A.begin(), A.end(), [&](piii& a, piii& b) { return a.se.se < b.se.se; });
    vector<vector<int>> D(a+1, vector<int>(b+1, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= a; j++) {
            for(int k = 0; k <= b; k++) {
                int p = min(A[i].se.fi, k/A[i].se.se);
                int x = j-A[i].se.fi+p, y = k-p*A[i].se.se;
                if(x < 0) continue;
                D[x][y] = max(D[x][y], D[j][k]+A[i].fi);
            }
        }
    }
    int ans = 0;
    for(auto i : D) for(auto j : i) ans = max(ans, j);
    cout << ans << "\n";
    return 0;
}