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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

vector<ll> dijk(int s, vector<vector<pii>>& E) {
    priority_queue<pll, vector<pll>, greater<pll>> Q;
    vector<ll> D(E.size(), LLINF);
    Q.push({0LL, s}); D[s] = 0LL;
    while(Q.size()) {
        pll tmp = Q.top(); Q.pop();
        if(D[tmp.se] < tmp.fi) continue;
        for(auto i : E[tmp.se]) {
            if(i.se+tmp.fi >= D[i.fi]) continue;
            D[i.fi] = i.se+tmp.fi;
            Q.push({i.se+tmp.fi, i.fi});
        }
    }
    return D;
}

void solve(int is, int ie, int js, int je, vector<vector<ll>> &D, int idx, vector<ll> &C) {
    int im = is+ie>>1, jm = -1;
    for(int k = js; k <= min(im-1, je); k++) {
        ll t = D[idx-1][k]+(C[im]-C[k])*(im-k-1);
        if(jm == -1 || D[idx][im] > t) {
            D[idx][im] = t;
            jm = k;
        }
    }
    if(is+1 == ie) return;
    solve(is, im, js, jm, D, idx, C);
    solve(im, ie, jm, je, D, idx, C);
}

vector<ll> inputing(int n, int b, int r) {
    vector<vector<pii>> E(n), F(n);
    for(int i = 0; i < r; i++) {
        int u, v, l; cin >> u >> v >> l; --u, --v;
        E[u].push_back({v, l});
        F[v].push_back({u, l});
    }

    vector<ll> A = dijk(b, E), B = dijk(b, F);
    vector<ll> C(b, 0LL);
    for(int i = 0; i < b; i++) C[i] = A[i]+B[i];
    sort(C.begin(), C.end());
    vector<ll> G(b+1, 0LL);
    for(int i = 0; i < b; i++) G[i+1] = G[i]+C[i];
    return G;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, b, s, r; cin >> n >> b >> s >> r;
    vector<ll> C = inputing(n, b, r);

    vector<vector<ll>> D(s+1, vector<ll>(b+1, LLINF));
    D[0][0] = 0LL;
    for(int i = 1; i <= s; i++) solve(i, b+1, 0, b+1, D, i, C);
    cout << D[s][b] << "\n";
    return 0;
}