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

pll ext(ll a, ll b) {
    if(!b) return {a, {1, 0}};
    pll tmp = ext(b, a%b);
    return {tmp.fi, {tmp.se.se, tmp.se.fi-(a/b)*tmp.se.se}};
}
ll _inv(ll a, ll p) {
    pll tmp = ext(a, p);
    if(tmp.fi > 1) return -1LL;
    return mod(tmp.se.fi, p);
}

int dfs(int i, vector<int>& A, vector<vector<int>>& E, vector<bool>& vis) {
    if(vis[i]) return 0;
    vis[i] = true;
    for(auto j : E[i]) {
        if(A[j] == -1 || dfs(A[j], A, E, vis)) {
            A[j] = i;
            return 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> E(n);
    vector<int> A(m, -1);
    for(auto &i : E) {
        int x; cin >> x;
        i.resize(x);
        for(auto &j : i) {
            cin >> j;
            j--;
        }
    }
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        vector<bool> vis(n, false);
        cnt += dfs(i, A, E, vis);
    }
    cout << cnt << "\n";
    return 0;
}