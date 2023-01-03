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
    int n, k, x0, y0; cin >> n >> k >> x0 >> y0;
    vector<int> dp(k+1, INF);
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y; x -= x0, y -= y0;
        int s; cin >> s;
        switch(s) {
            case 1: y = -y; swap(x, y); break;
            case 2: x = -x; y = -y; break;
            case 0: x = -x; swap(x, y); break;
            default: break;
        }
        int c = max(-(x+y), -(y-x)), v;
        if(c <= 0) {
            c = 0;
            v = abs(x)+abs(y);
        } else {
            v = 2*abs(x);
        }
        //cout << x << " " << y << " " << c << " " << v << "\n";
        for(int j = k; j >= 0; j--) dp[min(j+v, k)] = min(dp[min(j+v, k)], dp[j]+c);
        dp[min(v, k)] = min(dp[min(v, k)], c);
    }
    //cout << dp;
    int ans = INF;
    for(int i = 0; i <= k; i++) ans = min(ans, k-i+dp[i]);
    cout << ans << "\n";
    return 0;
}