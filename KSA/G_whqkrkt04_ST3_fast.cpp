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
const int P = 998244353;
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

typedef vector<int> v;
typedef vector<v> vv;
typedef vector<vv> vvv;
typedef vector<vvv> vvvv;

typedef vector<pii> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<pii> d = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    vvvv dp(k, vvv(n, vv(m, v(d.size(), 0))));
    vector<vector<int>> chk(n, vector<int>(m));
    for(auto &i : chk) for(auto &j : i) {
        char c; cin >> c;
        j = (c == '#');
    }
    vvvvi points(n, vvvi(m, vvi(d.size())));
    for(int x = 0; x < n; x++) {
        for(int y = 0; y < m; y++) {
            for(int k = 0; k < d.size(); k++) {
                int xx = x+d[k].fi, yy = y+d[k].se;
                while(xx >= 0 && xx < n && yy >= 0 && yy < m && !chk[xx][yy]) {
                    points[x][y][k].push_back({xx, yy});
                    xx += d[k].fi, yy += d[k].se;
                }
            }
        }
    }
    int r, c; cin >> r >> c; --r, --c;
    for(int k = 0; k < d.size(); k++)
        for(auto &[xx, yy] : points[r][c][k])
            dp[0][xx][yy][k]++;
    for(int i = 1; i < dp.size(); i++) {
        vv T(n, v(m, 0));
        for(int x = 0; x < n; x++)
            for(int y = 0; y < m; y++)
                for(int k = 0; k < d.size(); k++)
                    T[x][y] = (T[x][y]+dp[i-1][x][y][k])%P;
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < m; y++) {
                for(int k = 0; k < d.size(); k++) {
                    int tmp = mod(T[x][y]-dp[i-1][x][y][k], P);
                    for(auto &[xx, yy] : points[x][y][k]) dp[i][xx][yy][k] = (dp[i][xx][yy][k]+tmp)%P;
                }
            }
        }
    }
    cin >> r >> c; --r, --c;
    int ans = 0;
    for(auto i : dp[k-1][r][c]) ans = (ans+i)%P;
    cout << ans << "\n";
    return 0;
}