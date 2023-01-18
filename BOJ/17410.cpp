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
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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

struct SqrtDecomp {
    int n, m;
    SqrtDecomp(int n) { this->n = n, m = (int)sqrt(n)+1; }
    pii trans(int k) { return {k/m, k%m}; }
    vector<pii> trans(int l, int r) {
        pii s = trans(l), e = trans(r);
        vector<pii> ret;
        if(s.fi < e.fi) {
            for(pii i = s; i.se < m; i.se++) ret.push_back(i);
            for(pii i = {s.fi+1, -1}; i.fi < e.fi; i.fi++) ret.push_back(i);
            for(pii i = {e.fi, 0}; i.se < e.se; i.se++) ret.push_back(i);
        } else {
            for(pii i = s; i.se < e.se; i.se++) ret.push_back(i);
        }
        return ret;
    }
};

void update(vector<vector<int>> &alcnt, vector<vector<int>> &sqcnt, vector<int> &A,
            SqrtDecomp &X, SqrtDecomp &Y, int x, int y, int val) {
    pii sqx = X.trans(x), sqy = Y.trans(y);
    vector<int> &sq = sqcnt[sqx.fi];
    for(int i = 0; i < sqy.fi; i++) sq[i] += val;
    vector<int> &al = alcnt[sqx.fi];
    for(int i = sqy.fi*Y.m; i < y; i++) al[i] += val;
    A[x] = y;
}

int query(vector<vector<int>> &alcnt, vector<vector<int>> &sqcnt, vector<int> &A,
            SqrtDecomp &X, SqrtDecomp &Y, int l, int r, int y) {
    vector<pii> sqx = X.trans(l, r);
    pii sqy = Y.trans(y);
    int ans = 0;
    //cout << sqx;
    for(auto &i : sqx) {
        if(i.se != -1) {
            int idx = i.fi*X.m+i.se;
            if(A[idx] > y) ans++;
        } else ans += alcnt[i.fi][y]+sqcnt[i.fi][sqy.fi];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    SqrtDecomp X(n), Y(10101);
    vector<int> A(n);
    vector<vector<int>> alcnt(X.m, vector<int>(Y.n, 0)), sqcnt(X.m, vector<int>(Y.m, 0));
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        update(alcnt, sqcnt, A, X, Y, i, x, 1);
    }
    //cout << " " << alcnt << " " << sqcnt;
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int t; cin >> t;
        if(t == 1) {
            int x, v; cin >> x >> v; --x;
            update(alcnt, sqcnt, A, X, Y, x, A[x], -1);
            update(alcnt, sqcnt, A, X, Y, x, v, 1);
        } else {
            int l, r, v; cin >> l >> r >> v; --l;
            cout << query(alcnt, sqcnt, A, X, Y, l, r, v) << "\n";
        }
        //cout << " " << alcnt << " " << sqcnt;
    }
    return 0;
}