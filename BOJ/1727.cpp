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

ll myabs(ll x) {
    if(x < 0) return -x;
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<ll> A(n), B(m);
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    if(n < m) { swap(n, m); swap(A, B); }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    vector<vector<ll>> C(n, vector<ll>(m, LLINF));
    C[0][0] = myabs(A[0]-B[0]);
    for(int j = 1; j < m; j++) C[j][j] = C[j-1][j-1]+myabs(A[j]-B[j]);
    for(int i = 1; i < n; i++) C[i][0] = min(C[i-1][0], myabs(A[i]-B[0]));
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < i; j++) {
            C[i][j] = min(C[i-1][j], C[i-1][j-1]+myabs(A[i]-B[j]));
        }
    }
    cout << C.back().back() << "\n";
    return 0;
}