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

pl dfs(int x, int p, string& A, vector<vector<int>>& E) {
    pl ret = {0LL, 0LL};
    for(auto &i : E[x]) {
        if(i == p) continue;
        pl tmp = dfs(i, x, A, E);
        ret.fi += tmp.fi;
        if(A[x] == '1') ret.fi += tmp.se*(tmp.se+1);
        else ret.se += tmp.se;
    }
    if(A[x] == '1') return {ret.fi, 1LL};
    else return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    string s; cin >> s;
    vector<vector<int>> E(n);
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            pl ans = dfs(i, -1, s, E);
            cout << ans.fi << "\n";
            return 0;
        }
    }
    cout << 0 << "\n";
}