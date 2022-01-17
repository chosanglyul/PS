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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    for(int tt = 1; tt <= t; tt++) {
        int ans = INF;
        string s; cin >> s;
        int vc = 0, cc = 0;
        vector<int> C(26);
        for(auto i : s) {
            C[i-'A']++;
            if(i == 'A' || i == 'E' || i == 'O' || i == 'I' || i == 'U') vc++;
            else cc++;
        }
        for(char c = 'A'; c-'A' < C.size(); c++) {
            if(c == 'A' || c == 'E' || c == 'O' || c == 'I' || c == 'U') ans = min(ans, 2*(vc-C[c-'A'])+cc);
            else ans = min(ans, 2*(cc-C[c-'A'])+vc);
        }
        cout << "Case #" << tt << ": " << ans << "\n";
    }
    return 0;
}