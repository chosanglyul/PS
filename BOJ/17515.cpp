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
ll myabs(ll x) { return (x > 0 ? x : -x); }

ll solve(int n, vector<int>& A, vector<int>& B, int a, int b) {
    vector<int> Q;
    for(int i = 0; i < n; i++) {
        if(B[i] > b) Q.push_back(i);
    }
    ll ans = 0LL;
    for(int i = 0, j = 0, k = 0; i < n; i++) {
        if(A[i] <= a) ans += myabs(i-Q[j++]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n), B(n);
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    if(n&1) cout << min(solve(n, A, B, n>>1, n+1>>1), solve(n, A, B, n+1>>1, n>>1)) << "\n";
    else cout << solve(n, A, B, n>>1, n>>1) << "\n";
    return 0;
}