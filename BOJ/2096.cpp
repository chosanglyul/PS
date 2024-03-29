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
    vector<int> dp(6, 0);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        vector<int> A(3), T(6);
        for(auto &i : A) cin >> i;
        
        T[0] = max(dp[0], dp[1])+A[0];
        T[1] = max(dp[0], max(dp[1], dp[2]))+A[1];
        T[2] = max(dp[1], dp[2])+A[2];

        T[3] = min(dp[3], dp[4])+A[0];
        T[4] = min(dp[3], min(dp[4], dp[5]))+A[1];
        T[5] = min(dp[4], dp[5])+A[2];

        dp = T;
    }
    cout << *max_element(dp.begin(), dp.end()) <<
        " " << *min_element(dp.begin(), dp.end()) << "\n";
    return 0;
}
