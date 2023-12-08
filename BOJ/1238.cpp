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

vector<int> solve(int x, vector<vector<pii>> &E) {
    vector<int> D(E.size(), INF); D[x] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> PQ;
    PQ.push({0, x});

    while(PQ.size()) {
        pii tmp = PQ.top(); PQ.pop();
        if(tmp.fi > D[tmp.se]) continue;
        for(auto &i : E[tmp.se]) {
            if(i.fi+tmp.fi >= D[i.se]) continue;
            D[i.se] = i.fi+tmp.fi;
            PQ.push({i.fi+tmp.fi, i.se});
        }
    }

    return D;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s; cin >> n >> m >> s; --s;
    vector<vector<pii>> E(n), F(n);
    for(int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c; --u, --v;
        E[u].push_back({c, v});
        F[v].push_back({c, u});
    }

    vector<int> A(n, 0);
    vector<int> C = solve(s, E);
    vector<int> D = solve(s, F);
    for(int i = 0; i < n; i++) A[i] = C[i]+D[i];
    cout << *max_element(A.begin(), A.end()) << "\n";
    return 0;
}
