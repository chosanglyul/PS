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
        vector<vector<int>> A(n, vector<int>(n));
        for(auto &i : A) for(auto &j : i) { cin >> j; j--; }
        ll ans = 0LL;
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
            vector<vector<pi>> T(n-i, vector<pi>(n-j));
            for(int x = 0; x < n-i; x++) for(int y = 0; y < n-j; y++) {
                T[x][y] = {A[x+i][y+j], A[x+i][y+j]};
                if(x) {
                    T[x][y].fi = min(T[x][y].fi, T[x-1][y].fi);
                    T[x][y].se = max(T[x][y].se, T[x-1][y].se);
                }
                if(y) {
                    T[x][y].fi = min(T[x][y].fi, T[x][y-1].fi);
                    T[x][y].se = max(T[x][y].se, T[x][y-1].se);
                }
                if(T[x][y].se - T[x][y].fi == (x+1) * (y+1) - 1) ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}