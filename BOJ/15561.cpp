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
    ll u, v;
    struct node {
        ll l, r, x, s;
        node() {}
        node(ll val, ll u, ll v) { this->l = this->r = this->x = this->s = u*val+v; }
        node(ll l, ll r, ll x, ll s) {
            this->l = l, this->r = r;
            this->x = x, this->s = s;
        }
        const node operator+(const node& b) {
            node res;
            res.l = max(this->l, this->s+b.l);
            res.r = max(b.r, this->r+b.s);
            res.x = max(max(this->x, b.x), this->r+b.l);
            res.s = this->s+b.s;
            return res;
        }
    };

    vector<node> seg;
    void init(int i, int s, int e, vector<ll>& A) {
        if(s+1 == e) seg[i] = node(A[s], u, v);
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    void update(int i, int s, int e, int j, ll x) {
        if(e <= j || s > j) return;
        if(s+1 == e) seg[i] = node(x, u, v);
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    node query(int i, int s, int e, int l, int r) {
        if(l >= e || s >= r) return {-LLINF, -LLINF, -LLINF, 0LL};
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    segtree(vector<ll>& A, ll u, ll v) {
        n = A.size();
        this->u = u, this->v = v;
        seg.resize(4*n);
        init(1, 0, n, A);
    }
    void update(int j, ll x) { update(1, 0, n, j, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r).x - v; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, u, v; cin >> n >> q >> u >> v;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    segtree S(A, u, v);
    while(q--) {
        int t; cin >> t;
        if(t) {
            int idx, val; cin >> idx >> val;
            S.update(--idx, val);
        } else {
            int l, r; cin >> l >> r; --l;
            cout << S.query(l, r) << "\n";
        }
    }
    return 0;
}