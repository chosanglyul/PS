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

    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    void update(int i, int s, int e, int j, int x) {
        if(e <= j || j < s) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(l <= s && e <= r) return seg[i];
        if(l >= e || s >= r) return 0;
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    segtree(vector<int>& A) {
        n = A.size();
        seg.resize(4*A.size());
        init(1, 0, n, A);
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(2*n), C(2*n);
    vector<pi> B(n, {-1, -1});
    for(int i = 0; i < 2*n; i++) {
        cin >> A[i]; A[i]--;
        if(B[A[i]].fi == -1) {
            B[A[i]].fi = i;
            C[i] = 1;
        } else {
            B[A[i]].se = i;
            C[i] = -1;
        }
    }
    segtree S(C);
    sort(B.begin(), B.end());
    ll ans = 0LL;
    for(int i = 0; i < n; i++) {
        S.update(B[i].fi, 0); S.update(B[i].se, 0);
        int tmp = S.query(B[i].fi, B[i].se);
        ans += tmp;
    }
    cout << 1+n+ans << "\n";
    return 0;
}