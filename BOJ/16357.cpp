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
        if(s+1 < e) {
            seg[i<<1] += lazy[i];
            seg[i<<1|1] += lazy[i];
            lazy[i<<1] += lazy[i];
            lazy[i<<1|1] += lazy[i];
        }
        lazy[i] = 0;
    }
    void update(int i, int s, int e, int l, int r, int x) {
        prop(i, s, e);
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i] += x;
            lazy[i] += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = max(seg[i<<1], seg[i<<1|1]);
        }
    }
    //int query(int i, int s, int e, int l, int r) {}

    public:
    segtree(int nn) {
        n = nn;
        seg = vector<int>(4*n, 0);
        lazy = vector<int>(4*n, 0);
    }
    void update(int l, int r, int x) { update(1, 0, n, l, r, x); }
    //int query(int l, int r) { return query(1, 0, n, l, r); }
    int query() { return seg[1]; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pi> A(n);
    vector<int> B;
    for(auto &i : A) {
        int x, y; cin >> x >> i.se >> y >> i.fi;
        B.push_back(i.fi); B.push_back(i.se);
    }
    vector<int> C(B);
    sort(C.begin(), C.end());
    C.erase(unique(C.begin(), C.end()), C.end());
    vector<pii> D;
    for(int i = 0; i < n; i++) {
        A[i].fi = lower_bound(C.begin(), C.end(), A[i].fi) - C.begin();
        A[i].se = lower_bound(C.begin(), C.end(), A[i].se) - C.begin();
        D.push_back({A[i].fi, {1, i}}); D.push_back({++A[i].se, {-1, i}});
    }
    sort(D.begin(), D.end());
    int cnt = 0, ans = 0;
    segtree S(C.size());
    for(auto &i : A) S.update(i.fi, i.se, 1);
    vector<int> E;
    for(auto &i : D) E.push_back(i.fi);
    sort(E.begin(), E.end());
    E.erase(unique(E.begin(), E.end()), E.end());
    for(int i = 0, j = 0; j < E.size(); j++) {
        for(; D[i].fi == E[j]; i++) {
            pi tmp = A[D[i].se.se];
            S.update(tmp.fi, tmp.se, -D[i].se.fi);
            cnt += D[i].se.fi;
        }
        ans = max(ans, cnt+S.query());
    }
    cout << ans << "\n";
    return 0;
}