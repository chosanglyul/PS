#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
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

int myabs(int x) { return (x > 0 ? x : -x); }
int getn(int x, int n) {
    int tmp = myabs(x); tmp--;
    if(x < 0) tmp += n;
    return tmp;
}

void dfs1(int x, vector<vector<int>>& E, vector<int>& S, vector<bool>& vis) {
    if(vis[x]) return;
    vis[x] = true;
    for(auto i : E[x]) dfs1(i, E, S, vis);
    S.push_back(x);
}

void dfs2(int x, int i, vector<vector<int>>& E, vector<int>& S, vector<int>& V, vector<bool>& vis) {
    if(vis[x]) return;
    vis[x] = true;
    S.push_back(x);
    V[x] = i;
    for(auto j : E[x]) dfs2(j, i, E, S, V, vis);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> m >> n;
    vector<vector<int>> E(2*n);
    while(m--) {
        int x, y; cin >> x >> y;
        E[getn(-x, n)].push_back(getn(y, n));
        E[getn(-y, n)].push_back(getn(x, n));
    }
    //cout << " " << E;
    vector<int> S, V(E.size());
    vector<bool> vis(E.size(), false);
    for(int i = 0; i < E.size(); i++)
        dfs1(i, E, S, vis);
    vector<vector<int>> SCC, EE(E.size());
    for(int i = 0; i < E.size(); i++)
        for(int j = 0; j < E[i].size(); j++)
            EE[E[i][j]].push_back(i);
    for(int i = 0; i < vis.size(); i++) vis[i] = false;
    reverse(S.begin(), S.end());
    //cout << S;
    for(int i = 0, j = 0; i < S.size(); i++) {
        if(vis[S[i]]) continue;
        SCC.push_back(vector<int>());
        dfs2(S[i], j++, EE, SCC.back(), V, vis);
    }
    //cout << " " << SCC;
    for(int i = 0; i < n; i++) {
        if(V[i] == V[i+n]) {
            cout << "OTL\n";
            return 0;
        }
    }
    cout << "^_^\n";
    return 0;
}