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

typedef struct line {
    pii a, b;
    line(pii x, pii y) { a = x, b = y; }
} line;

bool chk(vector<vector<ll>> M, const int k, const ll x, const ll ans) {
    static const vector<pii> d = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int cnt = 0, n = M.size(), m = M[0].size();
    queue<line> Q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(auto dd : d) {
                int x = dd.fi+i, y = dd.se+j;
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                Q.push(line({i, j}, {x, y}));
            }
        }
    }
    while(Q.size() && cnt <= k) {
        line tmp = Q.front(); Q.pop();
        ll &a = M[tmp.a.fi][tmp.a.se], &b = M[tmp.b.fi][tmp.b.se];
        while(abs(a-b) > ans) {
            pii nxt;
            if(a < b) a = x, nxt = tmp.a;
            else b = x, nxt = tmp.b;
            cnt++;
            for(auto dd : d) {
                int x = dd.fi+nxt.fi, y = dd.se+nxt.se;
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                Q.push(line(nxt, {x, y}));
            }
        }
    }
    return cnt <= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; ll x; cin >> n >> m >> k >> x;
    vector<vector<ll>> M(n, vector<ll>(m));
    for(auto &i : M) for(auto &j : i) cin >> j;
    ll l = 0LL, r = LLINF;
    while(l+1LL < r) {
        ll mi = l+r>>1;
        if(chk(M, k, x, mi-1LL)) r = mi;
        else l = mi;
    }
    cout << l << "\n";
    return 0;
}