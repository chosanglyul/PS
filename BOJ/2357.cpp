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
template <typename T>
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
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

struct RMQ {
    vector<vector<pii>> sparse;
    
    pii merge(pii &a, pii &b) {
        return {min(a.fi, b.fi), max(a.se, b.se)};
    }
    
    pii query(int s, int e) {
        if(s >= e) return {INF, -INF};
        int idx = __lg(e-s);
        return merge(sparse[idx][s], sparse[idx][e-(1<<idx)]);
    }

    RMQ(vector<int> &A) {
        sparse.resize(__lg(A.size())+1);
        sparse[0].resize(A.size());
        for(int i = 0; i < A.size(); i++) sparse[0][i] = {A[i], A[i]};
        for(int i = 1; i < sparse.size(); i++) {
            sparse[i].resize(A.size());
            for(int j = 0; j+(1<<(i-1)) < A.size(); j++)
                sparse[i][j] = merge(sparse[i-1][j], sparse[i-1][j+(1<<(i-1))]);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> A(n), B(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        A[i] = x;
    }
    RMQ rmq(A);
    for(int i = 0; i < m; i++) {
        int s, e; cin >> s >> e; --s;
        cout << rmq.query(s, e) << "\n";
    }
    return 0;
}