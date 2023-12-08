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

void dfs1(int x, vector<bool> &vis, vector<vector<int>> &E, vector<int> &st) {
    if(vis[x]) return;
    vis[x] = true;
    for(auto i : E[x]) dfs1(i, vis, E, st);
    st.push_back(x);
}

void dfs2(int x, vector<bool> &vis, vector<vector<int>> &E, vector<int> &T) {
    if(vis[x]) return;
    vis[x] = true;
    for(auto i : E[x]) dfs2(i, vis, E, T);
    T.push_back(x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> E(n), F(n);
        for(int i = 0; i < m; i++) {
            int u, v; cin >> u >> v; --u, --v;
            E[u].push_back(v);
            F[v].push_back(u);
        }
        vector<int> st;
        vector<bool> chk(n, false);
        for(int i = 0; i < n; i++) {
            if(chk[i]) continue;
            dfs1(i, chk, E, st);
        }
        vector<int> IDX(n);
        vector<vector<int>> SCC;
        fill(chk.begin(), chk.end(), false);
        while(st.size()) {
            int i = st.back(); st.pop_back();
            if(chk[i]) continue;
            vector<int> T;
            dfs2(i, chk, F, T);
            for(auto j : T) IDX[j] = SCC.size();
            SCC.push_back(T);
        }
        vector<int> indeg(SCC.size(), 0);
        for(int i = 0; i < n; i++) {
            for(auto j : E[i]) {
                if(IDX[i] == IDX[j]) continue;
                indeg[IDX[j]]++;
            }
        }
        int ans = 0;
        for(auto i : indeg) if(!i) ans++;
        cout << ans << "\n";
    }
    return 0;
}
