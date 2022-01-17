#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
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


struct line { ll y, c; int s, e, k; };

class segtree {
    private:
    int n;
    vector<deque<pll>> seg;

    void init(int i, int s, int e) {
        seg[i].push_back({0, 0});
        if(s+1 != e) {
            init(i<<1, s, s+e>>1);
            init(i<<1|1, s+e>>1, e);
        }
    }
    bool cmp(pll a, pll b, ll y) {
        ll aa = a.fi*y+a.se;
        ll bb = b.fi*y+b.se;
        return aa > bb;
    }
    void cle(int i, ll y) {
        while(seg[i].size() > 1 && cmp(seg[i][0], seg[i][1], y)) {
            seg[i].pop_front();
        }
    }
    void update(int i, int s, int e, int l, int r, pll x) {
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i].push_back(x);
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
        }
    }
    pll query(int i, int s, int e, int j, ll y) {
        cle(i, y);
        //cout << i << " " << s << " " << e << "  ";
        //for(auto &i : seg[i]) cout << i << "  ";
        //cout << "\n";
        if(s+1 == e) {
            return seg[i][0];
        } else {
            int mi = s+e>>1;
            pll tmp = ((j < mi) ? query(i<<1, s, mi, j, y) : query(i<<1|1, mi, e, j, y));
            ////cout << i << " " << s << " " << e << " " << tmp << "   ";
            return (cmp(seg[i][0], tmp, y) ? tmp : seg[i][0]);
        }
    }

    public:
    segtree(int n) {
        this->n = n;
        seg.resize(4*n);
        init(1, 0, n);
    }
    void update(int l, int r, pll x) { update(1, 0, n, l, r, x); }
    pll query(int j, ll y) { return query(1, 0, n, j, y); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<line> A(n);
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
        cout << i << "\n";
        D[A[i].k] = A[i].y*A[i].y;
        for(int j = A[i].s; j < A[i].e;) {
            pll tmp = S.query(j, A[i].y);
            int l = j, r = A[i].e;
            while(l+1 < r) {
                int mi = l+r>>1;
                pll que = S.query(mi, A[i].y);
                cout << "mi : " << mi << " " << que << "   ";
                if(que == tmp) l = mi;
                else r = mi;
            }
            j = r;
            cout << "j : " << j << " tmp : " << tmp << " ";
            //get j, upd j to get.e
            D[A[i].k] = min(D[A[i].k], A[i].y*A[i].y+A[i].y*tmp.fi+tmp.se);
            cout << "ans : " << D[A[i].k] << "\n";
        }
        S.update(A[i].s, A[i].e, {-2*A[i].y, A[i].y*A[i].y+D[A[i].k]+A[i].c});
        //upd [A[i].s, A[i].e)
        cout << "\n";
    }
    for(auto i : D) cout << i << "\n";
    return 0;
}