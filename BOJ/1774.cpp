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

struct UnionFind {
    vector<int> P;
    int fin(int x) {
        if(P[x] == x) return x;
        return P[x] = fin(P[x]);
    }
    void mer(int x, int y) {
        x = fin(x), y = fin(y);
        if(x == y) return;
        P[x] = y;
    }
    UnionFind(int n) {
        P.resize(n);
        for(int i = 0; i < n; i++) P[i] = i;
    }
};

typedef pair<ll, pair<int, int>> pdii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<pll> A(n);
    UnionFind uf(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        uf.mer(--u, --v);
    }

    vector<pdii> E;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(uf.fin(i) == uf.fin(j)) continue;
            E.push_back({(A[i].fi-A[j].fi)*(A[i].fi-A[j].fi)
                +(A[i].se-A[j].se)*(A[i].se-A[j].se), {i, j}});
        }
    }
    sort(E.begin(), E.end());

    double ans = 0.0;
    for(auto &i : E) {
        if(uf.fin(i.se.fi) == uf.fin(i.se.se)) continue;
        ans += sqrt(i.fi);
        uf.mer(i.se.fi, i.se.se);
    }
    cout << fixed << setprecision(2) << ans;
    return 0;
}
