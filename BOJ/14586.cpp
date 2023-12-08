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

int getdp(int s, int e, vector<vector<int>> &dp) {
    if(s > e) return 0;
    return dp[s][e];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> L(n), R(n);
    vector<pll> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    sort(A.begin(), A.end());
    for(int i = 0; i < n; i++) {
        ll tmp = A[i].fi+A[i].se;
        int j = i+1;
        while(j < n && A[j].fi <= tmp) {
            tmp = max(tmp, A[j].fi+A[j].se);
            j++;
        }
        R[i] = --j;
    }
    for(int i = n-1; i >= 0; i--) {
        ll tmp = A[i].fi-A[i].se;
        int j = i-1;
        while(j >= 0 && A[j].fi >= tmp) {
            tmp = min(tmp, A[j].fi-A[j].se);
            j--;
        }
        L[i] = ++j;
    }

    vector<vector<int>> dp(n, vector<int>(n, INF));
    for(int x = 0; x < n; x++) {
        for(int y = 0; y+x < n; y++) {
            for(int z = y; z <= x+y; z++) {
                int a = getdp(y, z-1, dp)+getdp(R[z]+1, x+y, dp)+1;
                int b = getdp(y, L[z]-1, dp)+getdp(z+1, x+y, dp)+1;
                dp[y][x+y] = min(dp[y][x+y], min(a, b));
            }
        }
    }
    cout << dp[0][n-1] << "\n";
    return 0;
}
