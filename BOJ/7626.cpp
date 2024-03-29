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

struct node { int x1, x2, y1, y2; };
struct query {
    int x, l, r, v;
    query(int xx, int tl, int rr, int vv) { x = xx, l = tl, r = rr, v = vv; }
};

class segtree {
    private:
    int n;
    vector<ll> seg, val, com;
    void update(int i, int s, int e, int l, int r, int x) {
        if(e <= l || r <= s) return;
        if(l <= s && e <= r) {
            seg[i] += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
        }
        if(seg[i]) val[i] = com[e]-com[s];
        else if(s+1 == e) val[i] = 0LL;
        else val[i] = val[i<<1]+val[i<<1|1];
    }

    public:
    segtree(vector<ll>& A) {
        n = ((int)A.size())-1; com = A;
        seg = vector<ll>(4*n, 0LL);
        val = vector<ll>(4*n, 0LL);
    }
    void update(int l, int r, int x) { update(1, 0, n, l, r, x); }
    ll query() { return val[1]; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<node> A(n);
    vector<ll> X, Y;
    for(auto &i : A) {
        cin >> i.x1 >> i.x2 >> i.y1 >> i.y2;
        X.push_back(i.x1); X.push_back(i.x2);
        Y.push_back(i.y1); Y.push_back(i.y2);
    }
    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    segtree S(Y);
    vector<query> B;
    for(auto &i : A) {
        int y1 = lower_bound(Y.begin(), Y.end(), i.y1) - Y.begin();
        int y2 = lower_bound(Y.begin(), Y.end(), i.y2) - Y.begin();
        B.push_back(query(lower_bound(X.begin(), X.end(), i.x1) - X.begin(), y1, y2, 1));
        B.push_back(query(lower_bound(X.begin(), X.end(), i.x2) - X.begin(), y1, y2, -1));
    }
    sort(B.begin(), B.end(), [&](query& a, query& b) {
        if(a.x == b.x) return a.v < b.v;
        return a.x < b.x;
    });
    ll ans = 0LL;
    for(int i = 0, j = 0; i+1 < X.size(); i++) {
        while(j < B.size() && B[j].x == i) {
            S.update(B[j].l, B[j].r, B[j].v);
            j++;
        }
        ans += S.query()*(X[i+1] - X[i]);
    }
    cout << ans << "\n";
    return 0;
}