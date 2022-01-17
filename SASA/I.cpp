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
    vector<ll> seg, lazy;
    void prop(int i, int s, int e) {
        if(s+1 < e) {
            lazy[i<<1] += lazy[i];
            lazy[i<<1|1] += lazy[i];
            seg[i<<1] += lazy[i];
            seg[i<<1|1] += lazy[i];
        }
        lazy[i] = 0LL;
    }
    void update(int i, int s, int e, int l, int r, ll x) {
        prop(i, s, e);
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            lazy[i] += x;
            seg[i] += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = max(seg[i<<1], seg[i<<1|1]);
        }
    }
    ll query(int i, int s, int e, int l, int r) {
        prop(i, s, e);
        if(r <= s || e <= l) return -LLINF;
        if(l <= s && e <= r) return seg[i];
        else return max(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }
    void insert(int i, int s, int e, int j, ll x) {
        prop(i, s, e);
        if(j < s || j >= e) return;
        if(s+1 == e) seg[i] = x;
        else {
            insert(i<<1, s, s+e>>1, j, x);
            insert(i<<1|1, s+e>>1, e, j, x);
            seg[i] = max(seg[i<<1], seg[i<<1|1]);
        }
    }
    
    public:
    segtree(int m) {
        n = m;
        seg = vector<ll>(4*n, -LLINF);
        lazy = vector<ll>(4*n, 0LL);
    }
    void update(int l, int r, ll x) {
        l = max(0, l); r = min(n, r);
        update(1, 0, n, l, r, x);
    }
    ll query(int l, int r) {
        l = max(0, l); r = min(n, r);
        return query(1, 0, n, l, r);
    }
    void insert(int j, ll x) { insert(1, 0, n, j, x); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<ll> A(n), B(n);
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    ll ans = 0LL;
    if(m > n) {
        for(auto i : A) ans += i;
    } else if(m == 1) {
        ll tmp = 0LL;
        for(int i = 0; i < n; i++) {
            ans = max(ans, A[i]+B[i]-tmp);
            tmp += A[i];
        }
    } else {
        segtree S(n+1);
        vector<ll> C(n+1, 0LL);
        S.insert(0, 0LL);
        for(int i = 1; i <= n; i++) {
            S.update(i-m, i, A[i-1]);
            C[i] = max(C[i-1]-A[i-1], S.query(i-m+1, i));
            S.insert(i, C[i-1]-A[i-1]);
            if(i >= m) ans = max(ans, S.query(i-m, i-m+1)+B[i-1]);
        }
        ans = max(ans, C.back());
    }
    cout << ans << "\n";
    return 0;
}