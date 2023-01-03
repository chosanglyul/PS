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

typedef struct Node {
    ll l, r, v, s;
} Node;

class segtree {
    int n;
    vector<Node> seg;
    Node mer(Node a, Node b) {
        Node ans;
        ans.l = max(a.l, a.s+b.l);
        ans.r = max(b.r, a.r+b.s);
        ans.v = max(a.r+b.l, max(a.v, b.v));
        ans.s = a.s+b.s;
        return ans;
    }
    void update(int i, int s, int e, int j, ll x) {
        if(e <= j || s > j) return;
        if(s+1 == e) {
            seg[i].s += x;
            seg[i].l = seg[i].r = seg[i].v = seg[i].s;
        } else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = mer(seg[i<<1], seg[i<<1|1]);
        }
    }
    Node query(int i, int s, int e, int l, int r) {
        if(e <= l || r <= s) return {0LL, 0LL, 0LL, 0LL};
        if(l <= s && e <= r) return seg[i];
        return mer(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(int n) {
        this->n = n;
        seg = vector<Node>(4*n, {0LL, 0LL, 0LL, 0LL});
    }
    void update(int j, ll x) { update(1, 0, n, j, x); }
    ll query() { return query(1, 0, n, 0, n).v; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<piii> A(n);
    vector<int> X, Y;
    for(auto &i : A) {
        cin >> i.se.fi >> i.se.se >> i.fi;
        X.push_back(i.se.fi);
        Y.push_back(i.se.se);
    }
    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    vector<vector<pii>> B(Y.size());
    for(auto &i : A) {
        i.se.fi = lower_bound(X.begin(), X.end(), i.se.fi) - X.begin();
        i.se.se = lower_bound(Y.begin(), Y.end(), i.se.se) - Y.begin();
        B[i.se.se].push_back({i.fi, i.se.fi});
    }

    ll ans = 0LL;
    for(int i = 0; i < B.size(); i++) {
        segtree S(X.size());
        for(int j = i; j < B.size(); j++) {
            for(auto &node : B[j]) S.update(node.se, node.fi);
            ans = max(ans, S.query());
            //cout << i << " " << j << " " << S.query() << "\n";
        }
    }
    cout << ans << "\n";
    return 0;
}