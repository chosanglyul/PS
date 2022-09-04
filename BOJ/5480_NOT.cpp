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
    vector<int> T;
    vector<pii> seg;
    void update(int i, int s, int e, int x) {
        if(s+1 == e) {
            seg[i].fi++;
        } else {
            int mi = s+e>>1;
            int& idx = x < mi ? seg[i].se.fi : seg[i].se.se;
            pii tmp = idx == -1 ? make_pair(0, make_pair(-1, -1)) : seg[idx];
            idx = seg.size(); seg.push_back(tmp);
            if(x < mi) update(idx, s, mi, x);
            else update(idx, mi, e, x);
            seg[i].fi = 0;
            if(seg[i].se.fi != -1) seg[i].fi += seg[seg[i].se.fi].fi;
            if(seg[i].se.se != -1) seg[i].fi += seg[seg[i].se.se].fi;
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(i == -1 || l >= e || s >= r) return 0;
        if(l <= s && e <= r) return seg[i].fi;
        return query(seg[i].se.fi, s, s+e>>1, l, r) + query(seg[i].se.se, s+e>>1, e, l, r);
    }
    
    public:
    segtree(int n) {
        this->n = n;
        T.push_back(0);
        seg = {{0, {-1, -1}}};
    }
    void update(int x) {
        int siz = seg.size();
        seg.push_back(seg[T.back()]);
        T.push_back(siz);
        update(siz, 0, n, --x);
    }
    int query(int i, int l, int r) {
        if(l > r) swap(l, r);
        return query(i, 0, n, --l, r);
    }
    int lst() { return T.back(); }
};

struct ship { int x1, y1, x2, y2, w; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, k, l; cin >> n >> k >> l;
        vector<ship> S(k);
        for(auto &i : S) cin >> i.x1 >> i.y1 >> i.x2 >> i.y2 >> i.w;
        segtree R(n), C(n);
        vector<pi> T;
        T.push_back({C.lst(), R.lst()});
        for(int i = 0; i < l; i++) {
            int a, b; cin >> a >> b;
            if(b) C.update(a);
            else R.update(a);
            T.push_back({C.lst(), R.lst()});
        }
        vector<int> A(l, 0);
        for(auto i : S) {
            int s = 0, e = l+1;
            while(s+1 < e) {
                int mi = s+e>>1;
                int ans = C.query(T[mi].fi, i.x1, i.x2) + R.query(T[mi].se, i.y1, i.y2);
                if(ans > 0) e = mi;
                else s = mi;
            }
            if(s < l) A[s] = max(A[s], i.w);
        }
        for(auto i : A) cout << i << "\n";
    }
    return 0;
}