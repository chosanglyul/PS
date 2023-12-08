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

void solve(pii x, int n, int sx, int ex, int sy, int ey, int &cnt, vector<vector<int>> &dp) {
    if(n == 1) {
        int tmp = ++cnt;
        for(int i = sx; i < ex; i++)
            for(int j = sy; j < ey; j++)
                if(x.fi != i || x.se != j) dp[i][j] = tmp;
        return;
    }
    int mx = sx+ex>>1, my = sy+ey>>1;
    int idx = (x.fi >= mx)*2+(x.se >= my);
    vector<pii> T;
    for(int i = 0; i < 4; i++) {
        pii xx;
        int sxx, exx, syy, eyy;
        if(i&1) syy = my, eyy = ey, xx.se = my;
        else syy = sy, eyy = my, xx.se = my-1;
        if(i&2) sxx = mx, exx = ex, xx.fi = mx;
        else sxx = sx, exx = mx, xx.fi = mx-1;
        if(i == idx) xx = x;
        T.push_back(xx);
        solve(xx, n-1, sxx, exx, syy, eyy, cnt, dp);
    }
    int tmp = ++cnt;
    for(int i = 0; i < 4; i++) {
        if(idx == i) continue;
        dp[T[i].fi][T[i].se] = tmp;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    pii x; cin >> x.se >> x.fi; --x.fi, --x.se;
    vector<vector<int>> dp(1<<n, vector<int>(1<<n, 0));
    int cnt = 0;
    solve(x, n, 0, 1<<n, 0, 1<<n, cnt, dp);
    dp[x.fi][x.se] = -1;
    for(int i = 0; i < (1<<n); i++) cout << dp[(1<<n)-1-i];
    return 0;
}
