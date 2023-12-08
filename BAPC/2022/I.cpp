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

struct conv {
    double x, y;
    string s, t;
};

double dfs(int i, int j, double x, vector<bool> &vis,
            vector<vector<pair<int, double>>> &E) {
    if(vis[i]) return -1;
    vis[i] = true;
    if(i == j) return x;
    for(auto &e : E[i]) {
        double res = dfs(e.fi, j, x*e.se, vis, E);
        if(res != -1) return res;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(20);
    int n, q; cin >> n >> q;
    string tmp;
    vector<conv> A(n);
    vector<string> S;
    for(int i = 0; i < n; i++) {
        cin >> A[i].x >> A[i].s >> tmp >> A[i].y >> A[i].t;
        S.push_back(A[i].s);
        S.push_back(A[i].t);
    }
    sort(S.begin(), S.end());
    S.erase(unique(S.begin(), S.end()), S.end());
    map<string, int> M;
    for(int i = 0; i < S.size(); i++) M[S[i]] = i;
    vector<vector<pair<int, double>>> E(M.size());
    for(int i = 0; i < n; i++) {
        int x = M[A[i].s], y = M[A[i].t];
        E[x].push_back({y, A[i].y/A[i].x});
        E[y].push_back({x, A[i].x/A[i].y});
    }
    for(int i = 0; i < q; i++) {
        double v; string s, t;
        cin >> v >> s >> tmp >> t;
        vector<bool> vis(M.size(), false);
        double ans = dfs(M[s], M[t], v, vis, E);
        if(ans == -1) cout << "impossible\n";
        else cout << ans << "\n";
    }
    return 0;
}