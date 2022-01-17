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

class segtree {
    private:
    int n;
    vector<int> seg;
    void update(int i, int s, int e, int j, int x) {
        if(j < s || j >= e) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(l <= s && e <= r) return seg[i];
        else if(r <= s || l >= e) return 0LL;
        else return query(i<<1, s, s+e>>1, l, r) + query(i<<1|1, s+e>>1, e, l, r);
    }
    
    public:
    segtree(int m) {
        n = m;
        seg.resize(4*n);
        for(auto &i : seg) i = 0;
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
};

void dfs(int x, int& cnt, vector<vector<int>>& E,
        vector<int>& I, vector<int>& O, vector<bool>& vis) {
    if(vis[x]) return;
    vis[x] = true;
    I[x] = cnt++;
    for(auto i : E[x]) dfs(i, cnt, E, I, O, vis);
    O[x] = cnt++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, c; cin >> n >> m >> c;
    vector<int> A(n);
    for(auto &i : A) { cin >> i; i--; }
    vector<vector<int>> E(n), B(c);
    for(int i = 0; i < n; i++)
        B[A[i]].push_back(i);
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    vector<pii> Q(m);
    for(int i = 0; i < m; i++) {
        Q[i].fi = i;
        cin >> Q[i].se.fi >> Q[i].se.se;
        --Q[i].se.fi;
    }
    sort(Q.begin(), Q.end(), [&](pii& a, pii& b) {
        if(a.se.se == b.se.se) return a.se.fi < b.se.fi;
        return a.se.se < b.se.se;
    });
    int cnt = 0;
    vector<int> I(n), O(n);
    vector<bool> vis(n, false);
    dfs(0, cnt, E, I, O, vis);
    ll ans = 0LL;
    segtree S(cnt);
    for(int i = 0, j = 0; i < m; i++) {
        while(j < Q[i].se.se) {
            for(auto k : B[j]) S.update(I[k], 1);
            j++;
        }
        ans += S.query(I[Q[i].se.fi], O[Q[i].se.fi]);
    }
    cout << ans%P << "\n";
    return 0;
}