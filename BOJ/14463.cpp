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

struct SegTree {
    private:
    int n;
    vector<int> seg;

    void update(int i, int s, int e, int j, int x) {
        if(e <= j || j < s) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }

    int query(int i, int s, int e, int l, int r) {
        if(e <= l || r <= s) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    SegTree(int n) { this->n = n; seg.resize(4*n, 0); }
    void update(int j, int x) { update(1, 0, n, j, x); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pii> IDX(n, {-1, -1});
    vector<int> A(2*n);
    for(auto &i : A) { cin >> i; --i; }
    for(int i = 0; i < A.size(); i++) {
        if(IDX[A[i]].fi == -1) IDX[A[i]].fi = i;
        else IDX[A[i]].se = i;
    }
    SegTree seg(2*n);
    for(int i = 0; i < n; i++) {
        seg.update(IDX[i].fi, 1);
        seg.update(IDX[i].se, -1);
    }
    ll ans = 0LL;
    for(int i = 0; i < 2*n; i++) {
        if(IDX[A[i]].fi == i) {
            ll tmp = seg.query(i+1, IDX[A[i]].se);
            seg.update(IDX[A[i]].se, 0);
            ans += tmp;
        }
    }
    cout << ans << "\n";
    return 0;
}
