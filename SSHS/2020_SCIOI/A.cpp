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

class segtree {
    private:
    int k, n;
    vector<int> seg, bit;
    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) {
            seg[i] = (A[s] == k);
            bit[i] = A[s];
        } else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
            bit[i] = bit[i<<1]&bit[i<<1|1];
        }
    }
    void update(int i, int s, int e, int l, int r, int x) {
        if(e <= l || r <= s || (bit[i]&x) == x) return;
        if(l <= s && e <= r) bit[i] |= x;
        if(s+1 == e) {
            seg[i] = (bit[i] == k);
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(e <= l || r <= s) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    segtree(int k, vector<int>& A) {
        n = A.size();
        this->k = k;
        seg.resize(4*n);
        bit.resize(4*n);
        init(1, 0, n, A);
    }
    void update(int l, int r, int x) { update(1, 0, n, l, r, x); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    segtree S(k, A);
    int m; cin >> m;
    while(m--) {
        int t, l, r; cin >> t >> l >> r; --t, --l;
        if(t == 0) {
            int x; cin >> x;
            S.update(l, r, x);
        } else {
            cout << S.query(l, r) << "\n";
        }
    }
    return 0;
}