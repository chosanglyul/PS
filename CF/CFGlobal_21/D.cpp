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
    vector<int> seg;
    void update(int i, int s, int e, int j, int x) {
        if(e <= j || s > j) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(s >= r || l >= e) return INF;
        if(l <= s && e <= r) return seg[i];
        return min(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(int n) {
        this->n = n;
        seg = vector<int>(4*n, INF);
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n), B(n, INF); B[0] = 0;
        for(auto &i : A) cin >> i;
        vector<pi> US = {{A[0], 0}}, LS = {{A[0], 0}};
        segtree U(n), L(n);
        U.update(0, B[0]); L.update(0, B[0]);
        for(int i = 1; i < n; i++) {
            while(US.size() && US.back().fi < A[i]) { U.update(US.back().se, INF); US.pop_back(); }
            while(LS.size() && LS.back().fi > A[i]) { L.update(LS.back().se, INF); LS.pop_back(); }
            int x = (US.size() ? US.back().se+1 : 0);
            int y = (LS.size() ? LS.back().se+1 : 0);
            B[i] = min(L.query(x, i+1), U.query(y, i+1))+1;
            U.update(i, B[i]); L.update(i, B[i]);
            US.push_back({A[i], i}); LS.push_back({A[i], i});
        }
        cout << B.back() << "\n";
    }
    return 0;
}