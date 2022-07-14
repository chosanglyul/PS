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

ll comb[2501][2501];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i=1; i<=2500; ++i) {
        comb[i][0] = 1;
        for (int j=1; j<i; ++j) {
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % P;
        }
        comb[i][i] = 1;
    }

    int n, k;
    cin >> n >> k;

    ll ans = 0;
    for (int i=0; i<=k-2; ++i) {
        ll curr = comb[k][i] * (k-i) % P;
        for (int j=0; j<n-1; ++j) {
            curr = curr * (k-i-1) % P;
        }
        if (i&1) {
            ans = (ans - curr + P) % P;
        } else {
            ans = (ans + curr) % P;
        }

    }
    cout << ans;

    return 0;
}