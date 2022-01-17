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
    public:
    ll n;
    vector<ll> seg, lazy;

    void prop(ll i, ll s, ll e) {
        if(s+1 != e) {
            seg[i<<1] = min(seg[i<<1], lazy[i]);
            seg[i<<1|1] = min(seg[i<<1|1], lazy[i]);
            lazy[i<<1] = min(lazy[i], lazy[i<<1]);
            lazy[i<<1|1] = min(lazy[i], lazy[i<<1|1]);
        }
        lazy[i] = LLINF;
    }
    void update(ll i, ll s, ll e, ll l, ll r, ll x) {
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i] = min(seg[i], x);
            lazy[i] = min(lazy[i], x);
        } else {
            prop(i, s, e);
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }
    ll query(ll i, ll s, ll e, ll l, ll r) {
        if(r <= s || e <= l) return LLINF;
        if(l <= s && e <= r) return seg[i];
        prop(i, s, e);
        return min(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(ll n) {
        this->n = n;
        seg.resize(4*n); lazy.resize(4*n);
        for(auto &i : seg) i = LLINF;
        for(auto &i : lazy) i = LLINF;
    }
    void update(ll l, ll r, ll x) { update(1, 0, n, l, r, x); }
    ll query(ll l, ll r) { return query(1, 0, n, l, r); }
    ll query(ll i) { return query(1, 0, n, i, i+1); }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, k, q; cin >> n >> k >> q;
    vector<vector<ll>> A(k), B(k);
    vector<ll> D = {-LLINF, LLINF};
    for(ll i = 0LL; i < n; i++) {
        ll x, y; cin >> x >> y;
        A[--y].push_back(x);
        D.push_back(x);
    }
    for(auto &i : A) sort(i.begin(), i.end());
    sort(D.begin(), D.end());
    D.erase(unique(D.begin(), D.end()), D.end());
    //cout << D;
    for(ll i = 0; i < k; i++) {
        for(auto j : A[i]) {
            ll tmp = lower_bound(D.begin(), D.end(), j) - D.begin();
            B[i].push_back(tmp);
        }
    }
    ll m = D.size();
    segtree E(m), F(m), G(m); // -1 0 1
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    ll l = 1, r = 0;
    for(ll i = 0LL; i < k; i++) {
        Q.push({A[i][0], {i, 0LL}});
        r = max(r, B[i][0]);
    }
    E.update(0, l, D[r]);
    F.update(l, r, D[r]-D[l]);
    G.update(r, m, -D[l]);
    //cout << l << " " << r << " " << D[l] << " " << D[r] << "\n";
    while(Q.size()) {
        pii tmp = Q.top();
        Q.pop();
        if(++tmp.se.se < A[tmp.se.fi].size()) {
            Q.push({A[tmp.se.fi][tmp.se.se], {tmp.se.fi, tmp.se.se}});
            r = max(r, B[tmp.se.fi][tmp.se.se]);
            tmp = Q.top();
            l = B[tmp.se.fi][tmp.se.se];
        } else break;
        //cout << l << " " << r << " " << D[l] << " " << D[r] << "\n";
        E.update(0, l, D[r]);
        F.update(l, r, D[r]-D[l]);
        G.update(r, m, -D[l]);
    }
    for(ll i = 0LL; i < q; i++) {
        ll pos; cin >> pos;
        ll idx = upper_bound(D.begin(), D.end(), pos) - D.begin(); --idx;
        ll x = E.query(idx), y = F.query(idx), z = G.query(idx);
        //cout << i << " " << idx << "    " << x << " " << y << " " << z << "\n";
        ll ans = LLINF;
        if(x < LLINF) ans = min(ans, x-pos);
        if(y < LLINF) ans = min(ans, y);
        if(z < LLINF) ans = min(ans, z+pos);
        cout << ans << "\n";
    }
    return 0;
}