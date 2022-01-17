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

class dp {
    public:
    int m = 10101;
    vector<vector<int>> D;
    dp(int n) { D = vector<vector<int>>(n, vector<int>(2*m, 0)); }
    bool ok(int i, int j) { return (i >= 0 && j >= -m && j < m); }
    void set(int i, int j, int x) { if(ok(i, j)) D[i][j+m] = x; }
    int get(int i, int j) {
        if(ok(i, j)) return D[i][j+m];
        else return -1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    if(n == 1) return 0;
    reverse(A.begin(), A.end());
    dp D(n);
    D.set(0, A[0], 1);
    for(int i = 1; i < n; i++) {
        for(int j = -D.m; j < D.m; j++) {
            if(D.get(i-1, j)) {
                D.set(i, A[i]-j, -1);
                if(i < n-1) D.set(i, A[i]+j, 1);
            }
        }
    }
    vector<int> E;
    int t = k, j;
    for(int i = n-1; i > 0; i--) {
        if(D.get(i, t) < 0) j = n-i;
        E.push_back(j);
        t = (t-A[i])*D.get(i, t);
    }
    reverse(E.begin(), E.end());
    for(auto i : E) cout << i << "\n";
    return 0;
}