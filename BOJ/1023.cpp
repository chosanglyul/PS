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

ll get(int n, int x, int y, vector<vector<ll>>& ncr) {
    if(n%2 || y > x) return 0LL;
    int k = n>>1;
    return ncr[n-x-y][k-y]-ncr[n-x-y][k+1-y];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 55;
    vector<vector<ll>> ncr(tt, vector<ll>(tt, 0LL));
    for(int i = 0; i < tt; i++) ncr[i][0] = 1LL;
    ncr[1][1] = 1LL;
    for(int i = 1; i < tt; i++)
        for(int j = 1; j < tt; j++)
            ncr[i][j] = ncr[i-1][j-1]+ncr[i-1][j];
    int n; ll k; cin >> n >> k;
    if((1LL<<n) - get(n, 0, 0, ncr) <= k) {
        cout << -1 << "\n";
        return 0;
    }
    string s = ""; int x = 0, y = 0, chk = 0;
    for(int i = 0; i < n; i++) {
        if(y > x) chk = 1;
        ll tmp = get(n, x+1, y, ncr);
        if(chk) tmp = 0LL;
        ll cnt =  (1LL<<(n-i-1))-tmp;
        //cout << i << " " << x << " " << y << " " << k << " " << tmp << " " << cnt << "\n";
        if(cnt > k) x++, s += '(';
        else y++, s += ')', k -= cnt;
    }
    cout << s << "\n";
    return 0;
}