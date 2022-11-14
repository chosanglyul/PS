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

int myabs(int x) { return (x > 0 ? x : -x); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pii> A(n);
    for(int i = 0; i < n; i++) {
        cin >> A[i].fi;
        A[i].se = i;
    }
    sort(A.begin(), A.end());
    int m; cin >> m;
    vector<pii> B(m);
    for(int i = 0; i < m; i++) {
        cin >> B[i].fi;
        B[i].se = i;
    }
    sort(B.begin(), B.end());

    vector<vector<ll>> dp(n, vector<ll>(m, LLINF));
    dp[0][0] = myabs(A[0].fi - B[0].fi);
    for(int i = 1; i < n; i++) {
        dp[i][0] = dp[i-1][0] + myabs(A[i].fi - B[0].fi);
        for(int j = 1; j < m; j++)
            dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + myabs(A[i].fi - B[j].fi);
    }
    
    vector<int> C(n);
    int x = n-1, y = m-1;
    while(true) {
        C[x] = y;
        if(--x < 0) break;
        if(y > 0 && dp[x][y-1] < dp[x][y]) y--;
    }

    vector<int> R(n);
    ll ans = 0LL;
    for(int i = 0; i < n; i++) {
        ans += myabs(A[i].fi - B[C[i]].fi);
        R[A[i].se] = B[C[i]].se;
    }
    cout << ans << "\n";
    for(auto i : R) cout << i+1 << " ";
    cout << "\n";
    return 0;
}
