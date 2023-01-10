#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1024;
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

class seg_dynamic {
    private:
    vector<int> seg;
    void update(int i, int s, int e, int j, int x) {
        if(j < s || e <= j) return;
        if(s+1 == e) seg[i] += x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(e <= l || r <= s) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    seg_dynamic() {
        seg = vector<int>(4*INF, 0);
    }
    void update(int j, int x) { update(1, 0, INF, j, x); }
    int query(int l, int r) { return query(1, 0, INF, l, r); }
};

class seg_2d {
    private:
    vector<seg_dynamic> seg;
    void update(int i, int s, int e, int jx, int jy, int x) {
        if(e <= jy || s > jy) return;
        seg[i].update(jx, x);
        if(s+1 != e) {
            update(i<<1, s, s+e>>1, jx, jy, x);
            update(i<<1|1, s+e>>1, e, jx, jy, x);
        }
    }
    int query(int i, int s, int e, int xl, int xr, int yl, int yr) {
        if(e <= yl || yr <= s) return 0;
        if(yl <= s && e <= yr) return seg[i].query(xl, xr);
        return query(i<<1, s, s+e>>1, xl, xr, yl, yr) + query(i<<1|1, s+e>>1, e, xl, xr, yl, yr);
    }

    public:
    seg_2d() {
        seg = vector<seg_dynamic>(4*INF, seg_dynamic());
    }
    void update(int jx, int jy, int x) { update(1, 0, INF, jx, jy, x); }
    int query(int xl, int xr, int yl, int yr) { return query(1, 0, INF, xl, xr, yl, yr); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    seg_2d S;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int x; cin >> x;
            S.update(i, j, x);
        }
    }
    while(m--) {
        int w; cin >> w;
        if(w) {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            cout << S.query(--x1, x2, --y1, y2) << "\n";
        } else {
            int x, y, c; cin >> x >> y >> c; --x, --y;
            int tmp = S.query(x, x+1, y, y+1);
            S.update(x, y, c-tmp);
        }
    }
    return 0;
}