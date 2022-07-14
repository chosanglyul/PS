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
const int P = 1000000009;
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
    int n, m, k; cin >> n >> m >> k;
    vector<ll> A(n), B(m);
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    vector<vector<ll>> D(n, vector<ll>(m, 0LL));
    for(int i = 0; i < k; i++) {
        vector<vector<ll>> C(n+1, vector<ll>(m+1, (i == 0)));
        for(int x = 0; x < n; x++)
            for(int y = 0; y < m; y++)
                C[x+1][y+1] = mod(C[x][y+1]+C[x+1][y]-C[x][y]+D[x][y], P);
        for(int x = 0; x < n; x++)
            for(int y = 0; y < m; y++)
                D[x][y] = (A[x] > B[y] ? C[x][y] : 0LL);
    }
    ll ans = 0LL;
    for(auto &i : D) for(auto &j : i) ans = mod(ans+j, P);
    cout << ans << "\n";
    return 0;
}