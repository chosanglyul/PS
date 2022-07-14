#include <bits/stdc++.h>
using namespace std;
typedef __int128_t ll;
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

class segtree {
    private:
    int n;
    vector<int> seg;
    void update(int i, int s, int e, int j, int x) {
        if(e <= j || s > j) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1] + seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(s >= r || l >= e) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r) + query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    segtree(int n) {
        this->n = n;
        seg = vector<int>(4*n, 0);
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
};

bool cmp(pll x, pll y) {
    __int128_t a = (__int128_t)x.se.fi*y.se.se, b = (__int128_t)x.se.se*y.se.fi;
    if(a == b) return x.fi < y.fi;
    else return a < b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q; cin >> q;
    vector<pll> Q(q), A, B;
    for(int i = 0; i < q; i++) {
        long long x, y, z; cin >> x >> y;
        Q[i].fi = x;
        if(Q[i].fi == 1) {
            cin >> z;
            Q[i].se = {y, z};
            if(Q[i].se.fi > 0) A.push_back({i, Q[i].se});
            if(Q[i].se.fi < 0) B.push_back({i, Q[i].se});
        } else Q[i].se.fi = y;
    }
    sort(A.begin(), A.end(), cmp);
    sort(B.begin(), B.end(), cmp);
    //cout << A << B;
    segtree SA(A.size()), SB(B.size());
    pii cnt = {0, {0, 0}};
    for(int i = 0; i < q; i++) {
        if(Q[i].fi == 1LL) {
            if(Q[i].se.fi > 0LL) {
                int idx = lower_bound(A.begin(), A.end(), make_pair(i, Q[i].se), cmp) - A.begin();
                SA.update(idx, 1);
                //cout << Q[i].se << "   " << idx << "\n";
            }
            if(Q[i].se.fi < 0LL) {
                int idx = lower_bound(B.begin(), B.end(), make_pair(i, Q[i].se), cmp) - B.begin();
                SB.update(idx, 1);
                //cout << Q[i].se << "   " << idx << "\n";
            }
            if(Q[i].se.fi == 0LL) {
                if(Q[i].se.se == 0LL) cnt.fi++;
                if(Q[i].se.se < 0LL) cnt.se.fi++;
                if(Q[i].se.se > 0LL) cnt.se.se++;
            }
        } else {
            if(cnt.fi > 0LL) {
                cout << 0 << "\n";
                continue;
            }
            ll x = Q[i].se.fi;
            int tmpA = lower_bound(A.begin(), A.end(), make_pair(0, make_pair(1LL, -x)), cmp) - A.begin();
            int tmpB = lower_bound(B.begin(), B.end(), make_pair(0, make_pair(-1LL, x)), cmp) - B.begin();
            //cout << tmpA << " " << tmpB << "\n";
            if(tmpA < A.size() && A[tmpA].fi < i && (__int128_t)A[tmpA].se.fi*x+A[tmpA].se.se == 0) cout << 0 << "\n";
            else if(tmpB < B.size() && B[tmpB].fi < i && (__int128_t)B[tmpB].se.fi*x+B[tmpB].se.se == 0) cout << 0 << "\n";
            else {
                int ans = cnt.se.fi + SA.query(tmpA, A.size()) + SB.query(0, tmpB);
                if(ans&1) cout << "-\n";
                else cout << "+\n";
            }
        }
    }
    return 0;
}