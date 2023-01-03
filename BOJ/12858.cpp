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
    int n;
    vector<ll> seg;
    function<ll(ll, ll)> mer;
    void init(int i, int s, int e, vector<ll> &A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = mer(seg[i<<1], seg[i<<1|1]);
        }
    }
    ll query(int i, int s, int e, int l, int r) {
        if(e <= l || r <= s) return 0LL;
        if(l <= s && e <= r) return seg[i];
        return mer(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }
    void update(int i, int s, int e, int j, ll x) {
        if(e <= j || s > j) return;
        if(s+1 == e) seg[i] += x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = mer(seg[i<<1], seg[i<<1|1]);
        }
    }

    public:
    segtree(vector<ll> A, function<ll(ll, ll)> F) {
        mer = F;
        n = A.size();
        seg.resize(n*4);
        init(1, 0, n, A);
    }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
    void update(int j, ll x) { update(1, 0, n, j, x); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;

    vector<ll> B(n); B[0] = A[0];
    for(int i = 1; i < n; i++) B[i] = A[i]-A[i-1];
    segtree seg_sum(B, [](ll a, ll b) { return a+b; });

    vector<ll> C(B.begin()+1, B.end());
    segtree seg_gcd(C, [](ll a, ll b) { return __gcd(a, b); });

    int q; cin >> q;
    while(q--) {
        int t, a, b; cin >> t >> a >> b; a--;
        if(t) {
            seg_sum.update(a, t);
            seg_sum.update(b, -t);
            if(a > 0) seg_gcd.update(a-1, t);
            if(b < n) seg_gcd.update(b-1, -t);
        } else {
            ll x = seg_sum.query(0, b);
            ll y = abs(seg_gcd.query(a, b-1));
            cout << __gcd(x, y) << "\n";
        }
    }

    return 0;
}