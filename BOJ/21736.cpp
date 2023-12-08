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

int dfs(pii xy, vector<vector<bool>> &chk, vector<string> &S) {
    if(xy.fi < 0 || xy.fi >= S.size() || xy.se < 0 || xy.se >= S[xy.fi].size()) return 0;
    if(chk[xy.fi][xy.se] || S[xy.fi][xy.se] == 'X') return 0;
    chk[xy.fi][xy.se] = true;
    int ret = 0;
    if(S[xy.fi][xy.se] == 'P') ret++;
    const static vector<pii> dxy = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for(auto &i : dxy) ret += dfs({xy.fi+i.fi, xy.se+i.se}, chk, S);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<string> S(n);
    for(auto &i : S) cin >> i;
    pii xy;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(S[i][j] == 'I') xy = {i, j};

    vector<vector<bool>> chk(n, vector<bool>(m, false));
    int cnt = dfs(xy, chk, S);
    if(cnt == 0) cout << "TT\n";
    else cout << cnt << "\n";
    return 0;
}
