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
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n+1, 0);
        for(int i = 0; i < n; i++) {
            int x; cin >> x;
            A[i+1] = A[i]+x;
        }
        vector<vector<int>> DP(n+1, vector<int>(n+1, INF));
        vector<vector<int>> opt(n+1, vector<int>(n+1, -1));
        for(int i = 0; i < n; i++) {
            DP[i][i+1] = 0LL;
            opt[i][i+1] = i;
        }
        for(int i = 2; i <= n; i++) {
            for(int j = 0; i+j <= n; j++) {
                for(int k = opt[j][i+j-1]; k <= opt[j+1][i+j]; k++) {
                    int tmp = DP[j][k]+DP[k][i+j]+A[i+j]-A[j];
                    if(opt[j][i+j] == -1 || DP[j][i+j] > tmp) {
                        DP[j][i+j] = tmp;
                        opt[j][i+j] = k;
                    }
                }
            }
        }
        cout << DP[0][n] << "\n";
    }
    return 0;
}