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
const int P = 998244353;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, qq; cin >> n >> qq;
    vector<vector<ll>> A(n+1, vector<ll>(n+1, 0LL)); A[0][0] = 1LL;
    ll p = mod(qq*inv(10000, P), P), q = mod((10000-qq)*inv(10000, P), P);
    vector<ll> prob(n+1, 0LL); prob[0] = 1LL;
    for(int i = 1; i <= n; i++) {
        ll tt = mod(A[i-1][0]*inv(2*i-1, P), P);
        for(int j = 0; j <= i; j++) {
            ll tmp = inv(2*i-1, P);
            if(j < n) A[i][j] = mod(A[i][j]+mod(A[i-1][j+1]*tmp, P)*p, P);
            if(j > 0) A[i][j] = mod(A[i][j]+mod(A[i-1][j-1]*tmp, P)*q, P);
            A[i][j] = mod(A[i][j]+A[i-1][j]*tmp+A[i-1][j], P);
            if(j == 0) A[i][j] = mod(A[i][j]*tt, P);
        }
        prob[i] = mod(prob[i-1]*(1LL-mod(tt*q, P)), P);
    }
    cout << " " << A;
    cout << prob;
    cout << prob[n] << "\n";
    return 0;
}