#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
typedef pair<int, ll> pil;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
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
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

void dfs(int x, int d, vector<int>& D, vector<vector<pil>>& E, vector<vector<pil>>& A) {
    D[x] = d++;
    for(auto i : E[x]) {
        if(A[i.fi].size()) continue;
        A[i.fi].push_back({x, i.se});
        dfs(i.fi, d, D, E, A);
    }
}

int lca(int u, int v, vector<int>& D, vector<vector<pil>>& A) {
    if(D[u] > D[v]) swap(u, v);
    for(int i = 29; i >= 0; i--)
        if(D[A[v][i].fi] >= D[u])
            v = A[v][i].fi;
    if(v == u) return v;
    for(int i = 29; i >= 0; i--) {
        if(A[v][i].fi != A[u][i].fi) {
            v = A[v][i].fi;
            u = A[u][i].fi;
        }
    }
    return A[v][0].fi;
}

ll len(int u, int v, vector<int>& D, vector<vector<pil>>& A) {
    if(u == v) return 0LL;
    if(D[u] > D[v]) swap(u, v);
    ll tmp = 0LL;
    for(int i = 29; i >= 0; i--) {
        if(D[A[v][i].fi] >= D[u]) {
            tmp += A[v][i].se;
            v = A[v][i].fi;            
        }
    }
    return tmp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<pil>> A(n), E(n);
    for(int i = 0; i < n-1; i++) {
        int x, y, z; cin >> x >> y >> z; --x, --y;
        E[x].push_back({y, z});
        E[y].push_back({x, z});
    }
    vector<int> D(n);
    A[0].push_back({0, 0LL});
    dfs(0, 0, D, E, A);
    for(int i = 1; i < 30; i++) {
        for(int j = 0; j < n; j++) {
            pil a = A[j][i-1];
            pil b = A[a.fi][i-1];
            A[j].push_back({b.fi, b.se+a.se});
        }
    }
    int q; cin >> q;
    while(q--) {
        int t, u, v; cin >> t >> u >> v; --u, --v;
        int l = lca(u, v, D, A);
        if(t == 1) {
            cout << len(u, l, D, A)+len(l, v, D, A) << "\n";
        } else {
            int k; cin >> k; k--;
            int mi = D[u]-D[l], le = D[u]+D[v]-2*D[l];
            if(k > mi) {
                k = le-k;
                swap(u, v);
            }
            int tu = u;
            for(int i = 29; i >= 0; i--)
                if(D[A[u][i].fi]+k >= D[tu])
                    u = A[u][i].fi;
            cout << u+1 << "\n";
        }
    }
    return 0;
}