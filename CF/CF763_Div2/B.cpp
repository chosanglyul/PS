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

void solve(int l, int r, vector<vector<bool>>& chk) {
    if(l == r) {
        cout << l << " " << r << " " << l << "\n";
    } else if(chk[l+1][r]) {
        cout << l << " " << r << " " << l << "\n";
        solve(l+1, r, chk);
    } else if(chk[l][r-1]) {
        cout << l << " " << r << " " << r << "\n";
        solve(l, r-1, chk);
    } else {
        for(int d = l+1; d < r; d++) {
            if(chk[l][d-1] && chk[d+1][r]) {
                cout << l << " " << r << " " << d << "\n";
                solve(l, d-1, chk);
                solve(d+1, r, chk);
                return;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<vector<bool>> chk(n+1, vector<bool>(n+1, false));
        for(int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            chk[x][y] = true;
        }
        solve(1, n, chk);
        cout << "\n";
    }
    return 0;
}