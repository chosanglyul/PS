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
        if(s > j || e <= j) return;
        if(s+1 == e) seg[i] += x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(s >= r || l >= e) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    segtree(int nn) {
        n = nn;
        seg = vector<int>(4*n, 0);
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<pi> A(n);
        for(auto &i : A) cin >> i.fi >> i.se;
        sort(A.begin(), A.end());
        vector<pi> B(m), C(m), D, E;
        for(int i = 0; i < m; i++) {
            cin >> B[i].fi >> B[i].se;
            cin >> C[i].fi >> C[i].se; C[i].se++;
            D.push_back({B[i].fi, i});
            E.push_back({B[i].se, i});
        }
        sort(D.begin(), D.end());
        sort(E.begin(), E.end());
        segtree S(101010);
        ll ans = 0LL;
        int dd = 0, ee = 0;
        for(int i = 0, j = 0; i < 101010; i++) {
            while(dd < D.size() && D[dd].fi == i) {
                int idx = D[dd++].se;
                ans -= S.query(C[idx].fi, C[idx].se);
            }
            while(j < A.size() && A[j].fi == i) S.update(A[j++].se, 1);
            while(ee < E.size() && E[ee].fi == i) {
                int idx = E[ee++].se;
                ans += S.query(C[idx].fi, C[idx].se);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}