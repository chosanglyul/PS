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
    int x, y, z; cin >> x >> y >> z;
    int a = z, b = y, c = x-y-z;
    if(a > c) swap(a, c);
    if(a == b && b == c && c == a) {
        if(a == 1 || a == 4) cout << 2 << "\n";
        else if(a == 2 || a == 3) cout << 3 << "\n";
        else cout << 0 << "\n";
    } else if(a == b) {
        if(a == 1 || a == 2) cout << 1 << "\n";
        else cout << 0 << "\n";
    } else if(b == c) {
        if(c >= 7) cout << 0 << "\n";
        else {
            vector<bool> dp(c+1, false); dp[0] = true;
            for(int i = 1; i <= c; i++) {
                if(a != i && b != i)
                    for(int j = c-i; j >= 0; j--)
                        dp[i+j] = dp[i+j] || dp[j];
            }
            int ans = c;
            for(int i = 0; i <= c; i++)
                if(dp[i]) ans = min(ans, c-i);
            cout << ans << "\n";
        }
    } else if(c == a) {
        if(c >= 5) cout << 0 << "\n";
        else {
            vector<bool> dp(c+1, false); dp[0] = true;
            for(int i = 1; i <= c; i++) {
                if(b != i && a != i)
                    for(int j = c-i; j >= 0; j--)
                        dp[i+j] = dp[i+j] || dp[j];
            }
            int ans = c;
            for(int i = 0; i <= c; i++)
                if(dp[i]) ans = min(ans, c-i);
            cout << ans << "\n";
        }
    } else {
        cout << 0 << "\n";
    }
    return 0;
}
