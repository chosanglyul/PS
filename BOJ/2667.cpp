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

int dfs(int x, int y, vector<vector<char>>& A, vector<vector<bool>>& vis) {
    if(x < 0 || x >= vis.size() || y < 0 || y >= vis[x].size() || A[x][y] == '0' || vis[x][y]) return 0;
    vis[x][y] = true;
    static vector<pii> d = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int ret = 1;
    for(auto i : d) ret += dfs(x+i.fi, y+i.se, A, vis);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<char>> A(n, vector<char>(n)); cin >> A;
    vector<vector<bool>> vis(n, vector<bool>(n, false));
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(vis[i][j] || A[i][j] == '0') continue;
            ans.push_back(dfs(i, j, A, vis));
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << "\n";
    return 0;
}