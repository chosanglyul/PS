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
    vector<ll> seg;
    void init(int i, int s, int e, vector<ll>& A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    void set(vector<ll>& A) {
        n = A.size();
        seg.resize(4*n);
        init(1, 0, n, A);
    }
    void update(int i, int s, int e, int j, ll x) {
        if(j < s || j >= e) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    ll query(int i, int s, int e, int l, int r) {
        if(l <= s && e <= r) return seg[i];
        else if(r <= s || l >= e) return 0LL;
        else return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }
    
    public:
    segtree(vector<ll>& A) { set(A); }
    segtree(int siz) {
        vector<ll> A(siz);
        for(auto &i : A) cin >> i;
        set(A);
    }
    void update(int j, ll x) { update(1, 0, n, j, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    segtree s(n);
    int q = m+k;
    //cout << s.n << endl << s.seg;
    while(q--) {
        ll x, y, z; cin >> x >> y >> z;
        if(x == 1) s.update(--y, z);
        else cout << s.query(--y, z) << "\n";
        //cout << s.seg;
    }
    return 0;
}