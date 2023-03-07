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

pii add(pii a, pii b) { return {a.fi+b.fi, a.se+b.se}; }

pii solve(vector<vector<int>> &A, int xs, int xe, int ys, int ye) {
    bool a = true, b = true;
    for(int i = xs; i < xe; i++) {
        for(int j = ys; j < ye; j++) {
            if(A[i][j]) b = false;
            else a = false;
        }
    }
    if(a) return {1, 0};
    if(b) return {0, 1};
    pii ret = {0, 0};
    ret = add(ret, solve(A, xs, xs+xe>>1, ys, ys+ye>>1));
    ret = add(ret, solve(A, xs+xe>>1, xe, ys, ys+ye>>1));
    ret = add(ret, solve(A, xs, xs+xe>>1, ys+ye>>1, ye));
    ret = add(ret, solve(A, xs+xe>>1, xe, ys+ye>>1, ye));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> A(n, vector<int>(n));
    for(auto &i : A) for(auto &j : i) cin >> j;
    pii ans = solve(A, 0, n, 0, n);
    cout << ans.se << "\n" << ans.fi << "\n";
    return 0;
}