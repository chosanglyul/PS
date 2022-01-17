#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<pi, pi> piii;
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


struct line { int y, s, e, c, k; };
vector<line> A;

class segtree {
    private:
    int n;
    vector<pii> seg;
    const pii inf = {-2, {-1, -1}};

    void init(int i, int s, int e) {
        if(s+1 == e) {
            seg[i] = {-1, {0, n}};
        } else {
            seg[i] = inf;
            init(i<<1, s, s+e>>1);
            init(i<<1|1, s+e>>1, e);
        }
    }
    pii mer(pii a, pii b) {
        if(a.fi < 0) return b;
        if(b.fi < 0) return a;
        if(A[a.fi].y > A[b.fi].y) return a;
        return b;
    }
    void prop(int i, int s, int e) {
        if(s+1 != e && seg[i] != inf) {
            seg[i<<1] = mer(seg[i<<1], seg[i]);
            seg[i<<1|1] = mer(seg[i<<1|1], seg[i]);
            seg[i] = inf;
        }
    }
    void update(int i, int s, int e, int l, int r, pii x) {
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i] = x;
        } else {
            prop(i, s, e);
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
        }
    }
    pii query(int i, int s, int e, int j) {
        if(s+1 == e) {
            return seg[i];
        } else {
            prop(i, s, e);
            int mi = s+e>>1;
            if(j < mi) return query(i<<1, s, mi, j);
            else return query(i<<1|1, mi, e, j);
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
    A.resize(n); //(y, c), (s, e)
    vector<int> C;
    for(int i = 0; i < n; i++) {
        A[i].k = i;
        cin >> A[i].y >> A[i].s >> A[i].e >> A[i].c;
        C.push_back(A[i].s); C.push_back(A[i].e);
    }
    sort(C.begin(), C.end());
    C.erase(unique(C.begin(), C.end()), C.end());
    for(auto &i : A) {
        i.s = lower_bound(C.begin(), C.end(), i.s) - C.begin();
        i.e = lower_bound(C.begin(), C.end(), i.e) - C.begin(); i.e++;
    }
    sort(A.begin(), A.end(), [&](line a, line b) { return a.y < b.y; });
    segtree S(C.size());
    vector<ll> D(n);
    for(int i = 0; i < A.size(); i++) {
        //cout << i << "    ";
        D[A[i].k] = (ll)A[i].y*A[i].y;
        for(int j = A[i].s; j < A[i].e;) {
            pii tmp = S.query(j);
            j = tmp.se.se;
            //cout << tmp << "   ";
            if(tmp.fi == -1) continue;
            ll cha = A[i].y-A[tmp.fi].y;
            D[A[i].k] = min(D[A[i].k], D[A[tmp.fi].k]+cha*cha);
            //get j, upd j to get.e
        }
        if(A[i].s > 0) {
            pii tmp = S.query(A[i].s-1);
            S.update(tmp.se.fi, A[i].s, {tmp.fi, {tmp.se.fi, A[i].s}});
        }
        if(A[i].e < C.size()) {
            pii tmp = S.query(A[i].e);
            S.update(A[i].e, tmp.se.se, {tmp.fi, {A[i].e, tmp.se.se}});
        }
        S.update(A[i].s, A[i].e, {i, {A[i].s, A[i].e}});
        //get A[i].s-1, upd range [get.s, A[i].s) A[i].s == 0 check
        //get A[i].e, upd range [A[i].e, get.e) A[i].e == B.size() check
        //upd [A[i].s, A[i].e)
        //cout << "\n";
    }
    for(auto i : D) cout << i << "\n";
    return 0;
}