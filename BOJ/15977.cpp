#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 202020;
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

class seg_dynamic {
    private:
    typedef struct Node {
        int l, r, v;
    } Node;
    vector<Node> seg;
    void update(int i, int s, int e, int j, int x) {
        if(s+1 == e) seg[i].v = max(seg[i].v, x);
        else {
            int mi = s+e>>1;
            if(mi > j) {
                if(seg[i].l == -1) {
                    seg[i].l = seg.size();
                    seg.push_back({-1, -1, 0});
                }
                update(seg[i].l, s, mi, j, x);
                seg[i].v = max(seg[i].v, seg[seg[i].l].v);
            } else {
                if(seg[i].r == -1) {
                    seg[i].r = seg.size();
                    seg.push_back({-1, -1, 0});
                }
                update(seg[i].r, mi, e, j, x);
                seg[i].v = max(seg[i].v, seg[seg[i].r].v);
            }
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(i < 0 || e <= l || r <= s) return 0;
        if(l <= s && e <= r) return seg[i].v;
        return max(query(seg[i].l, s, s+e>>1, l, r), query(seg[i].r, s+e>>1, e, l, r));
    }

    public:
    seg_dynamic() {
        seg.push_back({-1, -1, 0});
    }
    void update(int j, int x) {
        //cout << "update : " << j << " " << x << "\n";
        update(0, 0, INF, j, x);
    }
    int query(int l, int r) {
        //cout << "query : " << l << " " << r << "\n";
        return query(0, 0, INF, l, r);
    }
};

class seg_2d {
    private:
    vector<seg_dynamic> seg;
    void update(int i, int s, int e, int jx, int jy, int x) {
        if(e <= jy || s > jy) return;
        seg[i].update(jx, x);
        if(s+1 != e) {
            update(i<<1, s, s+e>>1, jx, jy, x);
            update(i<<1|1, s+e>>1, e, jx, jy, x);
        }
    }
    int query(int i, int s, int e, int xl, int xr, int yl, int yr) {
        if(e <= yl || yr <= s) return 0;
        if(yl <= s && e <= yr) return seg[i].query(xl, xr);
        return max(query(i<<1, s, s+e>>1, xl, xr, yl, yr), query(i<<1|1, s+e>>1, e, xl, xr, yl, yr));
    }

    public:
    seg_2d() {
        seg = vector<seg_dynamic>(4*INF, seg_dynamic());
    }
    void update(int jx, int jy, int x) { update(1, 0, INF, jx, jy, x); }
    int query(int xl, int xr, int yl, int yr) { return query(1, 0, INF, xl, xr, yl, yr); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n; cin >> m >> n;
    if(m == 2) {
        vector<pii> A(n);
        for(auto &i : A) cin >> i.fi;
        for(auto &i : A) cin >> i.se;
        sort(A.begin(), A.end());
        vector<int> B;
        for(auto &i : A) {
            auto iter = lower_bound(B.begin(), B.end(), i.se);
            if(iter == B.end()) B.push_back(i.se);
            else *iter = i.se;
        }
        cout << B.size() << "\n";
    } else {
        vector<piii> A(n);
        for(auto &i : A) cin >> i.fi;

        vector<int> X;
        for(auto &i : A) {
            cin >> i.se.fi;
            X.push_back(i.se.fi);
        }
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        for(auto &i : A) i.se.fi = lower_bound(X.begin(), X.end(), i.se.fi) - X.begin();

        vector<int> Y;
        for(auto &i : A) {
            cin >> i.se.se;
            Y.push_back(i.se.se);
        }
        sort(Y.begin(), Y.end());
        Y.erase(unique(Y.begin(), Y.end()), Y.end());
        for(auto &i : A) i.se.se = lower_bound(Y.begin(), Y.end(), i.se.se) - Y.begin();

        seg_2d S;
        int ans = 0;
        sort(A.begin(), A.end());
        for(auto &i : A) {
            //cout << i << "\n";
            int tmp = S.query(0, i.se.fi+1, 0, i.se.se+1);
            ans = max(ans, ++tmp);
            S.update(i.se.fi, i.se.se, tmp);
            //cout << tmp << "\n";
        }
        cout << ans << "\n";
    }
    return 0;
}