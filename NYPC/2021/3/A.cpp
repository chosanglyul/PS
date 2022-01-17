#include <bits/stdc++.h>
using namespace std;
#define int ll
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
    public:
    int n;
    vector<pl> seg;

    pl mer(pl x, pl y) { return {x.fi+y.fi, x.se+y.se}; }
    void update(int i, int s, int e, int j, pl x) {
        if(j < s || j >= e) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = mer(seg[i<<1], seg[i<<1|1]);
        }
    }
    pl query(int i, int s, int e, int l, int r) {
        if(r <= s || e <= l) return {0LL, 0LL};
        if(l <= s && e <= r) return seg[i];
        return mer(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(int n) {
        this->n = n;
        seg.resize(4*n);
        for(auto &i : seg) i = {0, 0};
    }
    void update(int j, pl x) { update(1, 0, n, j, x); }
    pl query(int l, int r) { return query(1, 0, n, l, r); }
};

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n), C(n);
    for(auto &i : A) cin >> i;
    vector<pi> B(n);
    for(int i = 0; i < n; i++) B[i] = {A[i], i};
    sort(B.begin(), B.end());
    for(int i = 0; i < n; i++) C[B[i].se] = i;
    segtree S(n);
    ll ans = 0LL, tmp = 0LL;
    for(int i = 0, j = 0; i <= n-k; i++) { //[i, i+k)
        while(j < i+k) {
            pi l = S.query(0, C[j]);
            pi r = S.query(C[j], n);
            tmp += A[j]*l.se-l.fi-A[j]*r.se+r.fi;
            S.update(C[j], {(ll)A[j], 1LL});
            j++;
        }
        ans = max(ans, tmp);
        S.update(C[i], {0LL, 0LL});
        pi l = S.query(0, C[i]);
        pi r = S.query(C[i], n);
        tmp -= A[i]*l.se-l.fi-A[i]*r.se+r.fi;
    }
    cout << ans << "\n";
    return 0;
}