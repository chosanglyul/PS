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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<ll>> A(n, vector<ll>(n, LLINF)), B(n, vector<ll>(n+1, 0LL)), C(n, vector<ll>(n+1));
    for(int i = 0; i < n; i++) A[i][i] = 0LL;
    for(int i = 0; i < m; i++) {
        int s, e, d; cin >> s >> e >> d; s--, e--;
        A[s][e] = A[e][s] = d;
    }
    vector<pii> M(m);
    for(auto &i : M) {
        cin >> i.fi >> i.se.fi >> i.se.se; //s, u, t
        i.se.fi--;
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                A[j][k] = min(A[j][k], A[j][i]+A[i][k]);
    for(int i = 0; i < n; i++) {
        ll len = 0LL;
        //B[i][i+1] = ;
        for(int j = i+2; j <= n; j++) {
            ll tmp = M[j-1].se.se - M[j-2].se.se;
            len += A[M[j-2].se.fi][M[j-1].se.fi];
            B[i][j] = min(B[i][j-1], len-M[j-1].fi)+tmp;
        }
    }
    for(int i = 0; i < n; i++) {
        ll mi = LLINF;
        for(int j = 0; j < i; j++) mi = min(mi, C[j][i]);
        for(int j = i+1; j <= n; j++) C[i][j] = (i > 0 ? B[i][j] : max(B[i][j], mi));
    }
    ll ans = LLINF;
    for(int i = 0; i < n; i++) ans = min(ans, C[i][n]);
    cout << ans << "\n";
    return 0;
}