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

int dfs1(int x, vector<vector<pii>>& E, vector<bool>& chk) {
    if(chk[x]) return -1;
    chk[x] = true;
    int ret = 0;
    for(auto &i : E[x]) {
        int tmp = dfs1(i.fi, E, chk);
        if(tmp == -1) continue;
        ret += tmp;
        i.se.se = tmp;
    }
    return ++ret;
}

int dfs2(int x, vector<vector<pii>>& E) {
    for(auto &i : E[x])
        if(i.se.se*2 > (int)E.size())
            return dfs2(i.fi, E);
    return x;
}

pl dfs3(int x, int p, vector<vector<pii>>& E) {
    pl ans = {0LL, 1LL};
    for(auto &i : E[x]) {
        if(i.fi == p) continue;
        pl tmp = dfs3(i.fi, x, E);
        ans.fi += tmp.fi + tmp.se*i.se.fi;
        ans.se += tmp.se;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while(true) {
        int n; cin >> n;
        if(!n) return 0;
        vector<vector<pii>> E(n);
        vector<bool> chk(n, false);
        for(int i = 1; i < n; i++) {
            int x, y, z; cin >> x >> y >> z;
            E[x].push_back({y, {z, -1}});
            E[y].push_back({x, {z, -1}});
        }
        dfs1(0, E, chk);
        int idx = dfs2(0, E);
        fill(chk.begin(), chk.end(), false);
        cout << dfs3(idx, -1, E).fi << "\n";
    }
    return 0;
}