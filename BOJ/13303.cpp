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
    vector<pi> seg;
    void init(int i, int s, int e, int x) {
        seg[i] = {x, -1};
        if(s+1 < e) {
            init(i<<1, s, s+e>>1, x);
            init(i<<1|1, s+e>>1, e, x);
        }
    }
    pi query(int i, int s, int e, int j) {
        if(s > j || e <= j) return {INF, -1};
        if(s+1 < e) {
            pi l = query(i<<1, s, s+e>>1, j);
            pi r = query(i<<1|1, s+e>>1, e, j);
            return min(seg[i], min(l, r));
        } else return seg[i];
    }
    void update(int i, int s, int e, int l, int r, pi x) {
        if(s >= r || l >= e) return;
        if(l <= s && e <= r) seg[i] = min(seg[i], x);
        else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
        }
    }

    public:
    segtree(int m, int x) {
        n = m;
        seg = vector<pi>(4*n);
        init(1, 0, n, x);
    }
    int query(int j) { return query(1, 0, n, j).se; }
    void update(int l, int r, pi x) { update(1, 0, n, l, r, x); }
};

int ab(int x) { return (x < 0 ? -x : x); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s, e; cin >> n >> s >> e;
    vector<pii> A(n);
    vector<int> X, Y = {s};
    for(auto &i : A) {
        cin >> i.fi >> i.se.fi >> i.se.se;
        X.push_back(i.fi);
        Y.push_back(i.se.fi);
        Y.push_back(i.se.se);
    }
    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());
    segtree S((int)Y.size(), e);
    vector<pi> E(n, {-1, -1});
    for(int i = 0; i < n; i++) {
        int l = lower_bound(Y.begin(), Y.end(), A[i].se.fi) - Y.begin();
        int r = lower_bound(Y.begin(), Y.end(), A[i].se.se) - Y.begin();
        E[i] = {S.query(l), S.query(r)};
        S.update(l, r+1, {A[i].fi, i});
    }
    int k = S.query(lower_bound(Y.begin(), Y.end(), s) - Y.begin());
    if(k < 0) {
        cout << e << "\n" << 1 << " " << s << "\n";
        return 0;
    }
    vector<int> D(2*n, INF);
    priority_queue<pi, vector<pi>, greater<pi>> Q;
    D[k] = s-A[k].se.fi; Q.push({D[k], k});
    D[k+n] = A[k].se.se-s; Q.push({D[k+n], k+n});
    while(Q.size()) {
        pi tmp = Q.top(); Q.pop();
        int hre = tmp.se%n, dst = tmp.fi;
        int nxt = (tmp.se < n ? E[hre].fi : E[hre].se);
        int hey = (tmp.se < n ? A[hre].se.fi : A[hre].se.se);
        if(dst > D[tmp.se] || nxt < 0) continue;
        if(D[nxt] > dst+ab(hey-A[nxt].se.fi)) {
            D[nxt] = dst+ab(hey-A[nxt].se.fi);
            Q.push({D[nxt], nxt});
        }
        if(D[nxt+n] > dst+ab(hey-A[nxt].se.se)) {
            D[nxt+n] = dst+ab(hey-A[nxt].se.se);
            Q.push({D[nxt+n], nxt+n});
        }
    }
    int ans = INF;
    vector<int> F;
    for(int i = 0; i < 2*n; i++) {
        int nxt = (i < n ? E[i%n].fi : E[i%n].se);
        int hey = (i < n ? A[i%n].se.fi : A[i%n].se.se);
        if(nxt != -1) continue;
        int tmp = D[i]+e;
        if(ans > tmp) {
            ans = tmp;
            F.clear();
        }
        if(ans == tmp) F.push_back(hey);
    }
    sort(F.begin(), F.end());
    F.erase(unique(F.begin(), F.end()), F.end());
    cout << ans << "\n" << F.size() << " " << F;
    return 0;
}