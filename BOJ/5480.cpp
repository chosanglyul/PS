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
    int n;
    vector<int> seg, X;
    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(s >= r || l >= e) return INF;
        if(l <= s && e <= r) return seg[i];
        return min(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }
    void update(int i, int s, int e, int j, int x) {
        if(j >= e || j < s) return;
        if(s+1 == e) seg[i] = min(seg[i], x);
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }

    public:
    segtree(vector<int>& A) {
        X = A;
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        vector<int> T(X.size(), INF);
        this->n = T.size();
        seg.resize(4*n);
        init(1, 0, n, T);
    }
    int query(int l, int r) {
        l = lower_bound(X.begin(), X.end(), l) - X.begin();
        r = lower_bound(X.begin(), X.end(), r) - X.begin();
        return query(1, 0, n, l, r);
    }
    void update(int j, int x) {
        j = lower_bound(X.begin(), X.end(), j) - X.begin();
        update(1, 0, n, j, x);
    }
};

struct ship { int x1, y1, x2, y2, w; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, k, l; cin >> n >> k >> l;
        vector<ship> S(k);
        vector<int> XY;
        for(auto &i : S) {
            cin >> i.x1 >> i.y1 >> i.x2 >> i.y2 >> i.w;
            if(i.x1 > i.x2) swap(i.x1, i.x2);
            if(i.y1 > i.y2) swap(i.y1, i.y2);
            XY.push_back(i.x1); XY.push_back(++i.x2);
            XY.push_back(i.y1); XY.push_back(++i.y2);
        }
        vector<pi> T(l);
        for(auto &i : T) {
            cin >> i.fi >> i.se;
            XY.push_back(i.fi);
        }
        segtree R(XY), C(XY);
        for(int i = 0; i < l; i++) {
            if(T[i].se) C.update(T[i].fi, i);
            else R.update(T[i].fi, i);
        }
        vector<int> A(l, 0);
        for(auto i : S) {
            int tmp = min(C.query(i.x1, i.x2), R.query(i.y1, i.y2));
            if(tmp < INF) A[tmp] = max(A[tmp], i.w);
        }
        for(auto i : A) cout << i << "\n";
    }
    return 0;
}