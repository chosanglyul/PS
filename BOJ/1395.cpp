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
    vector<int> seg, lazy;
    void prop(int i, int s, int e) {
        if(s+1 != e && lazy[i]) {
            int mi = s+e>>1;
            seg[i<<1] = mi-s-seg[i<<1];
            seg[i<<1|1] = e-mi-seg[i<<1|1];
            lazy[i<<1] ^= 1;
            lazy[i<<1|1] ^= 1;
            lazy[i] = 0;
        }
    }
    void update(int i, int s, int e, int l, int r) {
        prop(i, s, e);
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i] = e-s-seg[i];
            lazy[i] ^= 1;
        } else {
            update(i<<1, s, s+e>>1, l, r);
            update(i<<1|1, s+e>>1, e, l, r);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        prop(i, s, e);
        if(r <= s || e <= l) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    segtree(int nn) {
        n = nn;
        seg = vector<int>(4*n, 0);
        lazy = vector<int>(4*n, 0);
    }
    int query(int l, int r) { return query(1, 0, n, l, r); }
    void update(int l, int r) { update(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    segtree S(n);
    while(m--) {
        int t, s, e; cin >> t >> s >> e; --s;
        if(t) cout << S.query(s, e) << "\n";
        else S.update(s, e);
    }
    return 0;
}