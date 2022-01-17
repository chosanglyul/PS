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

void dfs(int x, int idx, vector<vector<int>>& E, vector<bool>& chk, vector<int>& SCC) {
    if(chk[x]) return;
    chk[x] = true;
    for(auto i : E[x]) dfs(i, idx, E, chk, SCC);
    SCC[x] = idx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<vector<int>> B(m), C(n);
    for(int i = 0; i < B.size(); i++) {
        int x; cin >> x;
        B[i].resize(x);
        for(auto &j : B[i]) {
            cin >> j;
            C[--j].push_back(i);
        }
    }
    vector<vector<int>> E(2*m);
    for(int i = 0; i < n; i++) {
        if(!A[i]) {
            E[C[i][0]].push_back(C[i][1]+m);
            E[C[i][1]].push_back(C[i][0]+m);
            E[C[i][0]+m].push_back(C[i][1]);
            E[C[i][1]+m].push_back(C[i][0]);
        } else {
            E[C[i][0]].push_back(C[i][1]);
            E[C[i][1]].push_back(C[i][0]);
            E[C[i][0]+m].push_back(C[i][1]+m);
            E[C[i][1]+m].push_back(C[i][0]+m);
        }
    }
    vector<bool> chk(2*m, false);
    vector<int> SCC(2*m);
    int idx = 0;
    for(int i = 0; i < 2*m; i++)
        if(!chk[i]) dfs(i, idx++, E, chk, SCC);
    bool can = true;
    for(int i = 0; i < m; i++)
        if(SCC[i] == SCC[i+m]) can = false;
    if(can) cout << 1 << "\n";
    else cout << 0 << "\n";
    return 0;
}