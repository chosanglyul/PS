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
    int n;
    vector<ll> seg;
    vector<pll> lazy;
    
    void init(int i, int s, int e, vector<ll>& A) {
        lazy[i] = {0LL, {1LL, 0LL}};
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }

    void prop(int i, int s, int e) {
        if(s+1 == e) return;
        int mi = s+e>>1;
        if(lazy[i].fi) {
            lazy[i<<1] = lazy[i];
            lazy[i<<1|1] = lazy[i];
            ll tmp = (lazy[i].fi*lazy[i].se.fi+lazy[i].se.se)%P;
            seg[i<<1] = (mi-s)*tmp%P;
            seg[i<<1|1] = (e-mi)*tmp%P;
        } else {
            lazy[i<<1]
        }
        lazy[i] = {0LL, {1LL, 0LL}};
    }

    void update(int i, int s, int e, int l, int r, int t, ll x) {
        prop(i, s, e);
        if(s >= r || l >= e) return;
        if(l <= s && e <= r) {
            if(t == 1) {
                lazy[i].se.se = (lazy[i].se.se+x)%P;
                seg[i] = (seg[i]+x*(e-s))%P;
            }
            if(t == 2) {
                lazy[i].se.fi = (lazy[i].se.fi*x)%P;
                lazy[i].se.se = (lazy[i].se.se*x)%P;
                seg[i] = (seg[i]*x)%P;
            }
            if(t == 3) {
                lazy[i] = {x, {1LL, 0LL}};
                seg[i] = (x*(e-s))%P;
            }
        } else {
            update(i<<1, s, s+e>>1, l, r, t, x);
            update(i<<1|1, s+e>>1, e, l, r, t, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    
    ll query(int i, int s, int e, int l, int r) {
        prop(i, s, e);
        if(s >= r || l >= e) return 0LL;
        if(l <= s && e <= r) return seg[i];
    }

    public:
    segtree(vector<ll>& A) {
        n = A.size();
        init(1, 0, n, A);
    }
    void update(int l, int r, int t, ll x) {
        update(1, 0, n, l, r, t, x);
    }
    ll query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    int m; cin >> m;
    while(m--) {

    }
    return 0;
}