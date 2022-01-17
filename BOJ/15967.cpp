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
    vector<ll> seg, lazy;
    int n;
    void prop(int i, int s, int e) {
        if(s+1 < e && lazy[i]) {
            int mi = s+e>>1;
            seg[i<<1] += lazy[i]*(mi-s);
            seg[i<<1|1] += lazy[i]*(e-mi);
            lazy[i<<1] += lazy[i];
            lazy[i<<1|1] += lazy[i];
        }
        lazy[i] = 0LL;
    }
    void init(int i, int s, int e, vector<ll>& A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    ll query(int i, int s, int e, int l, int r) {
        prop(i, s, e);
        if(s >= r || l >= e) return 0LL;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }
    void update(int i, int s, int e, int l, int r, ll x) {
        prop(i, s, e);
        if(s >= r || l >= e) return;
        if(l <= s && e <= r) {
            seg[i] += x*(e-s);
            lazy[i] += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }

    public:
    segtree(vector<ll>& A) {
        n = A.size();
        seg = vector<ll>(4*n, 0LL);
        lazy = vector<ll>(4*n, 0LL);
        init(1, 0, n, A);
    }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
    void update(int l, int r, ll x) { update(1, 0, n, l, r, x); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q1, q2, q; cin >> n >> q1 >> q2; q = q1+q2;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    segtree S(A);
    while(q--) {
        int t; cin >> t; t--;
        int l, r; cin >> l >> r; --l;
        if(t) {
            ll x; cin >> x;
            S.update(l, r, x);
        } else cout << S.query(l, r) << "\n";
    }
    return 0;
}