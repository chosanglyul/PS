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

int mycha(int x, int y) {
    if(x > y) return x-y;
    else return y-x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    if(n <= 2) {
        cout << 0 << "\n";
        return 0;
    }
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int i = 2; i < n; i++) dp[i][0] = dp[i-1][0]+mycha(A[i], A[i-1]);
    for(int i = 2; i < n; i++) {
        for(int j = 1; j < i-1; j++)
            dp[i][j] = dp[i-1][j]+mycha(A[i], A[i-1]);
        for(int j = 1; j < i; j++)
            dp[i][i-1] += mycha(A[j], A[j-1]);
        for(int j = 0; j < i-1; j++)
            dp[i][i-1] = min(dp[i][i-1], dp[i-1][j]+mycha(A[j], A[i]));
    }
    int ans = INF;
    for(int i = 0; i < n-1; i++) ans = min(ans, dp.back()[i]);
    //cout << " " << dp;
    cout << ans << "\n";
    return 0;
}