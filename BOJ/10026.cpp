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

void dfs(int x, int y, vector<vector<char>> &map, vector<vector<bool>> &chk, vector<char> &C) {
    static vector<pii> d = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    if(x < 0 || x >= chk.size() || y < 0 || y >= chk[x].size()) return;
    if(chk[x][y] || find(C.begin(), C.end(), map[x][y]) == C.end()) return;
    chk[x][y] = true;
    for(auto i : d) dfs(x+i.fi, y+i.se, map, chk, C);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<char>> map(n, vector<char>(n));
    for(auto &i : map) for(auto &j : i) cin >> j;
    vector<vector<bool>> chk(n, vector<bool>(n, false));
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(chk[i][j]) continue;
            vector<char> C = {map[i][j]};
            dfs(i, j, map, chk, C);
            ans++;
        }
    }
    cout << ans << " ";
    ans = 0;
    chk = vector<vector<bool>>(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(chk[i][j]) continue;
            vector<char> C = {map[i][j]};
            if(map[i][j] == 'R' || map[i][j] == 'G') C = {'R', 'G'};
            dfs(i, j, map, chk, C);
            ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}