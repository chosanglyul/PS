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
    int n, m;
    vector<pi> seg;
    vector<int> lazy;
    void addi(int i, int x) { seg[i].fi += x, seg[i].se += x; }
    pi merg(pi a, pi b) { return {max(a.fi, b.fi), min(a.se, b.se)}; }
    void prop(int i, int s, int e) {
        if(s+1 < e) {
            addi(i<<1, lazy[i]);
            addi(i<<1|1, lazy[i]);
            lazy[i<<1] += lazy[i];
            lazy[i<<1|1] += lazy[i];
        }
        lazy[i] = 0;
    }
    void update(int i, int s, int e, int l, int r, int x) {
        prop(i, s, e);
        if(s >= r || l >= e) return;
        if(l <= s && e <= r) {
            addi(i, x);
            lazy[i] += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = merg(seg[i<<1], seg[i<<1|1]);
        }
    }
    pi query(int i, int s, int e, int l, int r) {
        prop(i, s, e);
        if(s >= r || l >= e) return {-INF, INF};
        if(l <= s && e <= r) return seg[i];
        return merg(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(int nn, int mm) {
        n = nn; m = mm;
        seg = vector<pi>(4*n, {0, 0});
        lazy = vector<int>(4*n, 0);
    }
    int update(int j, int x) { return update(j, j+1, x); }
    int update(int l, int r, int x) {
        pi tmp = query(1, 0, n, l, r);
        if(x < 0) x = -min(-x, tmp.se);
        else x = min(x, m-tmp.fi);
        update(1, 0, n, l, r, x);
        return x;
    }
    int query(int j) { return query(1, 0, n, j, j+1).fi; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q; cin >> n >> m >> q;
    segtree S(n, m);
    while(q--) {
        string s; cin >> s;
        if(s[0] == 's') {
            int j; cin >> j;
            cout << S.query(j) << "\n";
        } else if(s[0] == 'g') {
            int l, r, x; cin >> l >> r >> x;
            cout << S.update(l, ++r, x) << "\n";
        } else {
            int j, x; cin >> j >> x;
            cout << S.update(j, x) << "\n";
        }
    }
    return 0;
}