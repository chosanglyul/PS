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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << "   "; os << "\n"; return os; }
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
    vector<pl> seg;
    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) seg[i] = {0LL, A[s]};
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = {0LL, 0LL};
        }
    }
    void update(int i, int s, int e, int l, int r, int x) {
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i].fi += 1;
            seg[i].se += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
        }
    }
    ll query(int i, int s, int e, int j) {
        ll tmp = seg[i].fi*j+seg[i].se;
        if(s+1 == e) return tmp;
        else {
            int mi = s+e>>1;
            if(j >= mi) tmp += query(i<<1|1, mi, e, j);
            else tmp += query(i<<1, s, mi, j);
        }
        return tmp;
    }

    public:
    segtree(vector<int>& A) {
        n = A.size();
        seg.resize(4*n);
        init(1, 0, n, A);
    }
    void update(int l, int r, int x) { update(1, 0, n, l, r, x); }
    ll query(int j) { return query(1, 0, n, j); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    segtree S(A);
    int q; cin >> q;
    while(q--) {
        int t; cin >> t;
        if(t == 1) {
            int l, r; cin >> l >> r; --l;
            S.update(l, r, -l+1);
        } else {
            int x; cin >> x; --x;
            cout << S.query(x) << "\n";
        }
    }
    return 0;
}