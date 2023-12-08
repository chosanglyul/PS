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

/* https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/ExtendGCD.cpp */
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        cout << "Case #" << _t+1 << endl;
        int n; cin >> n;
        vector<pll> A(n);
        for(auto &i : A) cin >> i.fi >> i.se;
        vector<vector<ll>> dp(n, vector<ll>(n, LLINF));
        for(int i = 0; i < n; i++) {
            ll tmp = LLINF;
            for(int j = i+1; j < n; j++) {
                tmp = min(tmp, (A[j].se+A[i].se)*(A[j].fi-A[i].fi));
                dp[i][j] = tmp;
            }
        }
        int k; cin >> k;
        for(int i = 0; i < k; i++) {
            int a, b; cin >> a >> b; --a, --b;
            ll ans = LLINF;
            for(int j = a; j < b; j++) ans = min(ans, dp[j][b]);
            cout << ans << "\n";
        }
        cout.flush();
    }
    return 0;
}