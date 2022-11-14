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

struct TwoSat { // 1-based
    int n;
    vector<vector<int>> G, H;
    vector<vector<int>> SCC;
    vector<int> Chk, Stk, Id;

    TwoSat(int _n) {
        n = 2 * _n + 1; 
        G.resize(n); H.resize(n);
        Chk.resize(n); Id.resize(n);
    }
    void add(int x, int y) {
        if (x < 0) x += n;
        if (y < 0) y += n;
        G[n - x].push_back(y);
        H[y].push_back(n - x);
        G[n - y].push_back(x);
        H[x].push_back(n - y);
    }
    void dfs(int cur) {
        if (Chk[cur]) return; Chk[cur] = true;
        for (int x : G[cur]) dfs(x);
        Stk.push_back(cur);
    }
    void back_dfs(int cur, int idx) {
        if (Chk[cur]) return; Chk[cur] = true;
        SCC[idx].push_back(cur);
        Id[cur] = idx;
        for (int x : H[cur]) back_dfs(x, idx);
    }
    void get_SCC() {
        for (int i = 1; i < n; i++) {
            if (!Chk[i]) dfs(i);
        }
        fill(Chk.begin(), Chk.end(), false);
        while (!Stk.empty()) {
            int x = Stk.back(); Stk.pop_back();
            if (Chk[x]) continue;
            SCC.push_back(vector<int>(0));
            back_dfs(x, SCC.size() - 1);
        }
    }
    vector<bool> solve() {
        get_SCC();
        for (int i = 1; i <= n / 2; i++) {
            if (Id[i] == Id[n - i]) return vector<bool>(0);
        }
        vector<int> Ans(n, -1);
        for (int i = 0; i < SCC.size(); i++) {
            if (Ans[SCC[i][0]] != -1) continue;
            for (int x : SCC[i]) {
                Ans[x] = 0; Ans[n - x] = 1;
            }
        }
        vector<bool> ret(Ans.begin() + 1, Ans.begin() + 1 + n / 2);
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n; cin >> m >> n;
    TwoSat ts(m);
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        ts.add(x, y);
    }
    vector<bool> ret = ts.solve();
    if(ret.empty()) cout << 0;
    else cout << 1;
    return 0;
}