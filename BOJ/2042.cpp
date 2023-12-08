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

class IndexTree {
    private:
    int n;
    vector<ll> seg;

    public:
    IndexTree(vector<ll> &A) {
        n = A.size();
        seg.resize(2*n, 0LL);
        for(int i = 0; i < n; i++) seg[i+n] = A[i];
        for(int i = n-1; i; i--) seg[i] = seg[i<<1]+seg[i<<1|1];
    }

    ll query(int l, int r) {
        ll ans = 0LL;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l&1) ans += seg[l++];
            if(r&1) ans += seg[--r];
        }
        return ans;
    }

    void update(int i, ll x) {
        for(i += n; i; i >>= 1) seg[i] += x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    IndexTree s(A);
    int q = m+k;
    while(q--) {
        ll x, y, z; cin >> x >> y >> z;
        if(x == 1) {
            ll t = z-A[--y];
            A[y] = z;
            s.update(y, t);
        } else cout << s.query(--y, z) << "\n";
    }
    return 0;
}
