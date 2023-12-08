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

struct segtree {
    struct Node { int l, r, m, s; };

    int n;
    vector<Node> seg;

    Node merge(Node l, Node r) {
        return {
            (l.l == l.s ? l.l+r.l : l.l),
            (r.r == r.s ? r.r+l.r : r.r),
            max(l.r+r.l, max(l.m, r.m)),
            l.s+r.s
        };
    }

    void init(int i, int s, int e) {
        if(s+1 == e) seg[i] = {0, 0, 0, 1};
        else {
            init(i<<1, s, s+e>>1);
            init(i<<1|1, s+e>>1, e);
            seg[i] = merge(seg[i<<1], seg[i<<1|1]);
        }
    }

    void update(int i, int s, int e, int j, bool x) {
        if(j >= e || j < s) return;
        if(s+1 == e) {
            if(x) seg[i] = {1, 1, 1, 1};
            else seg[i] = {0, 0, 0, 1};
        } else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = merge(seg[i<<1], seg[i<<1|1]);
        }
    }

    Node query(int i, int s, int e, int l, int r) {
        if(r <= s || e <= l) return {0, 0, 0, 0};
        if(l <= s && e <= r) return seg[i];
        return merge(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    segtree(int n) {
        this->n = n;
        seg.resize(4*n);
        init(1, 0, n);
    }
};

struct Query {
    int l, r, s, e, w, idx;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pii> H(n);
    for(int i = 0; i < n; i++) {
        cin >> H[i].fi;
        H[i].se = i;
    }
    sort(H.begin(), H.end(), [](pii &a, pii &b) {
        return a.fi > b.fi;
    });
    int q; cin >> q;
    vector<Query> Q(q);
    for(int i = 0; i < q; i++) {
        Q[i].l = 1, Q[i].r = INF;
        cin >> Q[i].s >> Q[i].e >> Q[i].w; --Q[i].s;
        Q[i].idx = i;
    }
    while(true) {
        segtree S(n);
        for(int i = 0, j = 0; i < q; i++) {
            int m = Q[i].l+Q[i].r>>1;
            while(j < n && H[j].fi >= m) S.update(1, 0, n, H[j++].se, 1);
            if(S.query(1, 0, n, Q[i].s, Q[i].e).m >= Q[i].w) Q[i].l = m;
            else Q[i].r = m;
        }
        bool can = false;
        for(int i = 0; i < q; i++)
            if(Q[i].l+1 < Q[i].r)
                can = true;
        if(!can) break;
        sort(Q.begin(), Q.end(), [&](Query &x, Query &y) {
            return x.l > y.l;
        });
    }
    vector<int> ans(q);
    for(auto &i : Q) ans[i.idx] = i.l;
    for(auto i : ans) cout << i << "\n";
    return 0;
}
