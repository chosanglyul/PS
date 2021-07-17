#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<pi, pi> piii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

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

void dfs(int x, int d, int p, vector<int>& D, vector<int>& P, vector<bool>& vis, vector<vector<int>>& E) {
    if(vis[x]) return;
    vis[x] = true; D[x] = d; P[x] = p;
    for(auto &i : E[x]) dfs(i, d+1, x, D, P, vis, E);
}

void erase(vector<vector<int>>& E, int x, int y) {
    auto iter = find(E[y].begin(), E[y].end(), x);
    E[y].erase(iter);
    iter = find(E[x].begin(), E[x].end(), y);
    E[x].erase(iter);
}

void insert(vector<vector<int>>& E, int x, int y) {
    E[x].push_back(y);
    E[y].push_back(x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> E(n);
    vector<piii> B;
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        insert(E, --x, --y);
    }
    while(true) {
        int idx = -1;
        vector<bool> vis(n, false);
        vector<int> D(n, -1), P(n, -1);
        dfs(0, 0, -1, D, P, vis, E);
        for(int i = 0; i < n; i++) {
            if(D[i] == 3) {
                idx = i;
                B.push_back({{P[P[P[i]]], P[P[i]]}, {P[i], i}});
                erase(E, B.back().fi.fi, B.back().fi.se);
                erase(E, B.back().fi.se, B.back().se.fi);
                erase(E, B.back().se.fi, B.back().se.se);
                insert(E, B.back().fi.fi, B.back().se.fi);
                insert(E, B.back().fi.fi, B.back().se.se);
                insert(E, B.back().fi.se, B.back().se.se);
                break;
            }
        }
        if(idx == -1) break;
    }
    cout << B.size() << "\n";
    for(auto &i : B) cout << i.fi.fi+1 << " " << i.fi.se+1 << " " << i.se.fi+1 << " " << i.se.se+1 << "\n";
    return 0;
}