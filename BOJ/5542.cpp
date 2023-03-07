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

struct UF {
    vector<vector<pii>> P;
    vector<vector<int>> elements;
    int get(int t, vector<pii> &A) {
        auto iter = lower_bound(A.begin(), A.end(), pii(t, INF));
        return (--iter)->se;
    }
    int fin(int t, int x) {
        return get(t, P[x]);
    }
    void mer(int t, int x, int y) {
        x = P[x].back().se, y = P[y].back().se;
        if(x != y) {
            if(elements[x].size() > elements[y].size()) swap(x, y);
            for(auto i : elements[x]) {
                P[i].push_back({t, y});
                elements[y].push_back(i);
            }
            elements[x].clear();
        }
    }

    UF(int n) {
        P.resize(n), elements.resize(n);
        for(int i = 0; i < n; i++) {
            P[i].push_back({-INF, i});
            elements[i].push_back({i});
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k, q; cin >> n >> m >> k >> q;
    vector<vector<pii>> E(n);
    for(int i = 0; i < m; i++) {
        int x, y, z; cin >> x >> y >> z; --x, --y;
        E[x].push_back({y, z});
        E[y].push_back({x, z});
    }
    priority_queue<pii, vector<pii>, greater<pii>> que;
    vector<int> D(n, INF);
    for(int i = 0; i < k; i++) {
        int x; cin >> x; --x;
        D[x] = 0, que.push({0, x});
    }
    while(que.size()) {
        auto [dist, here] = que.top(); que.pop();
        if(dist > D[here]) continue;
        for(auto [next, val] : E[here]) {
            if(dist+val >= D[next]) continue;
            D[next] = dist+val;
            que.push({dist+val, next});
        }
    }
    UF uf(n);
    vector<pii> DV(n);
    for(int i = 0; i < n; i++) DV[i] = {D[i], i};
    sort(DV.begin(), DV.end(), greater<pii>());
    for(auto [dist, idx] : DV)
        for(auto [jdx, val] : E[idx])
            if(D[jdx] >= dist)
                uf.mer(-dist, idx, jdx);
    while(q--) {
        int x, y; cin >> x >> y; --x, --y;
        int s = 0, e = INF;
        while(s+1 < e) {
            int mi = s+e>>1;
            if(uf.fin(-mi, x) == uf.fin(-mi, y)) s = mi;
            else e = mi;
        }
        cout << s << "\n";
    }
    return 0;
}