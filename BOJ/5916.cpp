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
    vector<int> seg;

    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = max(seg[i<<1], seg[i<<1|1]);
        }
    }

    void update(int i, int s, int e, int j, int x) {
        if(e <= j || s > j) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = max(seg[i<<1], seg[i<<1|1]);
        }
    }

    int query(int i, int s, int e, int l, int r) {
        if(e <= l || r <= s) return 0;
        if(l <= s && e <= r) return seg[i];
        return max(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(vector<int>& A) {
        n = A.size();
        seg = vector<int>(4*n, 0);
        init(1, 0, n, A);
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
    int query(int l, int r) { return query(1, 0, n, l, r+1); }
};

typedef struct Node{ int siz, dep = 0, par = 0, in, out, top = 0; } Node;

void dfs1(int x, vector<vector<int>>& E, vector<Node>& A) {
    A[x].siz = 1;
    auto iter = find(E[x].begin(), E[x].end(), A[x].par);
    if(iter != E[x].end()) E[x].erase(iter);
    for(auto &i : E[x]) {
        A[i].par = x;
        A[i].dep = A[x].dep+1;
        dfs1(i, E, A);
        A[x].siz += A[i].siz;
        if(A[E[x][0]].siz < A[i].siz) swap(i, E[x][0]);
    }
}

void dfs2(int x, int& cnt, vector<vector<int>>& E, vector<Node>& A) {
    A[x].in = cnt++;
    for(auto &i : E[x]) {
        A[i].top = (i == E[x][0] ? A[x].top : i);
        dfs2(i, cnt, E, A);
    }
    A[x].out = cnt;
}

int query(int a, int b, segtree& S, vector<Node>& A) {
    int ret = 0;
    while(A[a].top != A[b].top) {
        if(A[A[a].top].dep < A[A[b].top].dep) swap(a, b);
        ret = max(ret, S.query(A[A[a].top].in, A[a].in));
        a = A[A[a].top].par;
    }
    if(A[a].dep > A[b].dep) swap(a, b);
    ret = max(ret, S.query(A[a].in+1, A[b].in));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> E(n);
    vector<pii> C;
    for(int i = 1; i < n; i++) {
        int x, y, z; cin >> x >> y >> z; --x, --y;
        E[x].push_back(y);
        E[y].push_back(x);
        C.push_back({z, {x, y}});
    }
    vector<Node> A(n);
    dfs1(0, E, A);
    int cnt = 0;
    dfs2(0, cnt, E, A);
    vector<int> B(n, 0);
    for(auto &i : C) {
        if(A[i.se.fi].dep < A[i.se.se].dep) swap(i.se.fi, i.se.se);
        B[A[i.se.fi].in] = i.fi;
    }
    segtree S(B);
    int m; cin >> m;
    while(m--) {
        int t, x, y; cin >> t >> x >> y;
        if(t == 1) S.update(A[C[--x].se.fi].in, y);
        else cout << query(--x, --y, S, A) << "\n";
    }
    return 0;
}