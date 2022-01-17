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
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

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
    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) {
            seg[i] = A[s];
        } else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }
    void update(int i, int s, int e, int l, int r, int x) {
        prop(i, s, e);
        if(l >= e || s >= r) return;
        if(l <= s && e <= r) {
            seg[i] += x;
            lazy[i] += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }
    int query(int i, int s, int e, int x) {
        prop(i, s, e);
        if(e <= x || s > x) return INF;
        if(s+1 == e) return seg[i];
        return min(query(i<<1, s, s+e>>1, x), query(i<<1|1, s+e>>1, e, x));
    }

    public:
    segtree(vector<int>& A) {
        n = A.size();
        seg.resize(4*n);
        lazy.resize(4*n);
        init(1, 0, n, A);
    }
    int query() { return seg[1]; }
    int query(int x) { return query(1, 0, n, x); }
    void update(int l, int r, int x) { if(l < r) update(1, 0, n, l, r, x); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<int> B(A);
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    for(auto &i : A) i = lower_bound(B.begin(), B.end(), i) - B.begin();
    vector<int> C(B.size(), 0);
    segtree T(C);
    ll su = 0LL;
    for(int i = 0; i < n; i++) {
        su += T.query(A[i]);
        T.update(0, A[i], 1);
    }
    segtree S(C);
    for(auto i : A) S.update(i+1, C.size(), 1);
    for(int i = 0; i < n; i++) {
        if(i) S.update(0, A[i-1], 1);
        S.update(A[i]+1, C.size(), -1);
        cout << su-S.query(A[i])+S.query() << " ";
    }
    cout << "\n";
    return 0;
}