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
    int n; cin >> n;
    vector<vector<int>> A(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            cin >> A[i][j];
    vector<vector<int>> B(n+1, vector<int>(n+1, 0)), C(n+1, vector<int>(n+1, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            B[i+1][j+1] = B[i+1][j]+B[i][j+1]-B[i][j]+(A[i][j] == 1);
            C[i+1][j+1] = C[i+1][j]+C[i][j+1]-C[i][j]+(A[i][j] == 2);
        }
    }
    vector<vector<pll>> D(n, vector<pll>(n, {0LL, 0LL}));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j+i < n; j++) {
            if(A[j][j+i] == 1) D[j][j+i].se = 0LL;
            else if(i == 0) D[j][j+i].se = 0LL;
            else {
                ll& tmp = D[j][j+i].se;
                for(int k = j; k < j+i; k++) {
                    int cnt1 = B[k+1][j+i+1]-B[j][j+i+1]-B[k+1][k+1]+B[j][k+1];
                    if(cnt1) continue;
                    tmp = (tmp+D[j][k].fi*D[k+1][j+i].fi)%P;
                    tmp = (tmp+D[j][k].fi*D[k+1][j+i].se)%P;
                }
            }
            int cnt2 = C[j+i+1][j+i+1]-C[j][j+i+1]-C[j+i+1][j]+C[j][j];
            if(cnt2) D[j][j+i].fi = 0LL;
            else D[j][j+i].fi = 1LL;
        }
    }
    
    cout << (2*(D[0][n-1].fi+D[0][n-1].se))%P << "\n";
    return 0;
}