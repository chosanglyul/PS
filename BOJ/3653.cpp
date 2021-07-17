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
    public:
    int n;
    vector<int> seg;
    int query(int i, int s, int e, int l, int r) { 
        if(r <= s || e <= l) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }
    void update(int i, int s, int e, int j, int x) {
        if(j < s || e <= j) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    public:
    segtree(vector<int>& A) {
        n = A.size();
        seg.resize(n*4);
        init(1, 0, n, A);
    }
    int query(int l, int r) {
        if(l >= r) return 0;
        return query(1, 0, n, l, r);
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<int> A(n+m, 1), B(n);
        for(int i = 0; i < m; i++) A[i] = 0;
        for(int i = 0; i < n; i++) B[i] = m+i;
        //cout << A << B;
        segtree s(A);
        for(int i = 0; i < m; i++) {
            int x; cin >> x; x--;
            cout << s.query(0, B[x]) << " ";
            s.update(B[x], 0);
            B[x] = m-i-1;
            s.update(B[x], 1);
            //cout << "\n" << B << s.seg;
        }
        cout << "\n";
    }
    return 0;
}