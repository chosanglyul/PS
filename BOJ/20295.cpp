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
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
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
    int n, t; cin >> n >> t;
    vector<vector<int>> dp(t+1, vector<int>(n, -INF));
    vector<pii> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    vector<vector<int>> B(n, vector<int>(n));
    for(auto &i : B) for(auto &j : i) cin >> j;

    for(int i = 0; i < n; i++)
        if(A[i].fi == 0) dp[0][i] = 0;
    for(int i = 0; i <= t; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if(j == k) {
                    int ii = i+1;
                    if(ii > t) continue;
                    dp[ii][k] = max(dp[ii][k], dp[i][j]+A[j].se);
                } else {
                    int ii = i+B[j][k];
                    if(ii > t || A[k].fi > dp[i][j]) continue;
                    dp[ii][k] = max(dp[ii][k], dp[i][j]);
                }
            }
        }
    }
    cout << *max_element(dp.back().begin(), dp.back().end()) << "\n";
    return 0;
}
