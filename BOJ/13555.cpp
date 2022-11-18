#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 5'000'000;
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

class segtree {
    private:
    int n, p;
    vector<ll> seg;
    void update(int i, int s, int e, int j, int x) {
        if(j < s || j >= e) return;
        if(s+1 == e) seg[i] = seg[i]+x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    ll query(int i, int s, int e, int l, int r) {
        if(l >= e || s >= r) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    segtree(int n) {
        this->n = n;
        seg = vector<ll>(4*n, 0LL);
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<pii> B;
    for(int i = 0; i < n; i++) B.push_back({A[i], -i});
    sort(B.begin(), B.end());

    vector<segtree> S(k, segtree(n));
    for(int i = 0; i < n; i++) {
        int idx = -B[i].se;
        S[0].update(idx, 1);
        for(int j = 1; j < k; j++) {
            int tmp = S[j-1].query(0, idx)%P;
            S[j].update(idx, tmp);
        }
    }
    cout << S.back().query(0, n)%P << "\n";
    return 0;
}