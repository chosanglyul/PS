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

struct query { int idx, s, e, x, y; };

struct UF {
    vector<int> P, A;

    int fin(int x) {
        if(P[x] == x) return x;
        else return P[x] = fin(P[x]);
    }

    void mer(int x, int y) {
        x = fin(x), y = fin(y);
        if(x != y) P[y] = x, A[x] += A[y];
    }

    UF(int n) {
        A.resize(n, 1);
        for(int i = 0; i < n; i++) P.push_back(i);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<piii> E(m);
    for(int i = 0; i < m; i++) {
        cin >> E[i].se.fi >> E[i].se.se >> E[i].fi;
        --E[i].se.fi, --E[i].se.se;
    }
    sort(E.begin(), E.end());
    int q; cin >> q;
    vector<query> Q(q);
    for(int i = 0; i < q; i++) {
        Q[i].s = 0, Q[i].e = m+1, Q[i].idx = i;
        cin >> Q[i].x >> Q[i].y;
        --Q[i].x, --Q[i].y;
    }
    vector<pii> ans(q);
    for(int _cnt = 0; _cnt < 20; _cnt++) {
        //for(auto i : Q) cout << i.idx << " " << i.s << " " << i.e << " " << i.x << " " << i.y << "\n";
        UF uf(n);
        for(int i = 0, idx = 0; i < Q.size(); i++) {
            if(Q[i].s+1 == Q[i].e) continue;
            int mi = Q[i].s+Q[i].e>>1;
            while(idx < mi) { uf.mer(E[idx].se.fi, E[idx].se.se); idx++; }
            if(uf.fin(Q[i].x) == uf.fin(Q[i].y)) Q[i].e = mi;
            else Q[i].s = mi;
        }
        sort(Q.begin(), Q.end(), [&](query &a, query &b) { return a.s < b.s; });
    }
    //for(auto i : Q) cout << i.idx << " " << i.s << " " << i.e << " " << i.x << " " << i.y << "\n";
    UF uf(n);
    for(int i = 0, idx = 0; i < Q.size(); i++) {
        if(Q[i].s == m) ans[Q[i].idx] = {-1, -1};
        else {
            while(idx <= Q[i].s) { uf.mer(E[idx].se.fi, E[idx].se.se); idx++; }
            ans[Q[i].idx] = {E[Q[i].s].fi, uf.A[uf.fin(Q[i].x)]};
        }
    }
    for(auto &i : ans) {
        if(i.fi == -1) cout << -1 << "\n";
        else cout << i << "\n";
    }
    return 0;
}