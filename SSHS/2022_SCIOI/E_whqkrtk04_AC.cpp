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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pii> d = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int n, m; cin >> n >> m;
    int xd, yd; cin >> xd >> yd; --xd, --yd;
    vector<vector<int>> V(n, vector<int>(m, INF));

    int k; cin >> k;
    for(int i = 0; i < k; i++) {
        int x, y; cin >> x >> y; --x, --y;
        V[x][y]++;
    }

    int t; cin >> t;
    for(int i = 0; i < t; i++) {
        int x, y; cin >> x >> y; --x, --y;
        cin >> V[x][y];
    }

    priority_queue<piii> Q;
    Q.push({INF, {xd, yd}});
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vis[xd][yd] = true;
    int dep = n*m, ans = 0;
    while(Q.size() && dep > 0) {
        piii top = Q.top(); Q.pop();
        //cout << dep << "  " << top << "\n";
        if(top.fi >= INF) {
            int cnt = min(dep, top.fi-INF);
            dep -= cnt, ans += cnt;
        } else {
            dep = min(top.fi-1, dep);
        }

        for(auto nxt : d) {
            nxt.fi += top.se.fi, nxt.se += top.se.se;
            if(nxt.fi < 0 || nxt.fi >= n || nxt.se < 0 || nxt.se >= m) continue;
            if(vis[nxt.fi][nxt.se]) continue;
            vis[nxt.fi][nxt.se] = true;
            Q.push({V[nxt.fi][nxt.se], nxt});
        }
    }
    cout << ans << "\n";
    return 0;
}