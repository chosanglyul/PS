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

vector<int> pi(const string& s) {
    int n = s.size();
    vector<int> ret(n, 0);
    int b = 1, m = 0;
    while (b+m < s.size()) {
        if (s[b+m] == s[m]) {
            ret[b+m] = m+1;
            m++;
        } else {
            if (m > 0) {
            b += m - ret[m-1];
            m -= ret[m-1];
            } else {
                b++;
            }
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    int d;
    cin >> s >> d;
    int n = s.size();

    vector<int> dp(n+1, 1e9);
    dp[0] = 0;
    vector<int> pmt = pi(s);
    cout << pmt;
    for (int i=1; i<=n; ++i) {
        dp[i] = dp[i-max(d, i-pmt[i-1])] + 1;
    }
    cout << dp[n];

    return 0;
}
