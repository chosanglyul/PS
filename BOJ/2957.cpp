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
    vector<pii> seg; //(depth, (start, end))
    void init(int i, int s, int e) {
        seg[i] = {0, {0, n}};
        if(s+1 != e) {
            init(i<<1, s, s+e>>1);
            init(i<<1|1, s+e>>1, e);
        }
    }
    void update(int i, int s, int e, int l, int r, pii x) {
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i] = x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
        }
    }
    pii query(int i, int s, int e, int j) {
        if(s+1 == e) return seg[i];
        else {
            int mi = s+e>>1;
            if(j >= mi) return max(seg[i], query(i<<1|1, mi, e, j));
            else return max(seg[i], query(i<<1, s, mi, j));
        }
    }

    public:
    segtree(int n) {
        this->n = n;
        seg.resize(4*n);
        init(1, 0, n);
    }
    void update(int l, int r, pii x) { update(1, 0, n, l, r, x); }
    pii query(int j) { return query(1, 0, n, j); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    segtree S(n);
    vector<int> A(n);
    for(auto &i : A) { cin >> i; i--; }
    ll ans = 0LL;
    for(int i = 0; i < n; i++) {
        pii tmp = S.query(A[i]);
        ans += tmp.fi;
        S.update(tmp.se.fi, A[i], {tmp.fi+1, {tmp.se.fi, A[i]}});
        S.update(A[i], tmp.se.se, {tmp.fi+1, {A[i], tmp.se.se}});
        cout << ans << "\n";
    }
    return 0;
}