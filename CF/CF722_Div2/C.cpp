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
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

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

ll myabs(ll a) { return (a > 0LL ? a : -a); }

pl solve(int x, int p, vector<vector<int>>& E, vector<pl>& A) {
    pl ret = {0LL, 0LL};
    for(auto &i : E[x]) {
        if(p == i) continue;
        pl tmp = solve(i, x, E, A);
        ret.fi += max(tmp.fi+myabs(A[x].fi-A[i].fi), tmp.se+myabs(A[x].fi-A[i].se));
        ret.se += max(tmp.fi+myabs(A[x].se-A[i].fi), tmp.se+myabs(A[x].se-A[i].se));
    }   
    //cout << x << " " << ret << "\n";
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<pl> A(n);
        for(auto &i : A) cin >> i.fi >> i.se;
        vector<vector<int>> E(n);
        vector<bool> vis(n, false);
        for(int i = 0; i < n-1; i++) {
            int x, y; cin >> x >> y; --x, --y;
            E[x].push_back(y);
            E[y].push_back(x);
        }
        pl tmp = solve(0, -1, E, A);
        cout << max(tmp.fi, tmp.se) << "\n";
    }
    return 0;
}