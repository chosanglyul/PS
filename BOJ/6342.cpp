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
    int n; cin >> n;
    vector<vector<int>> C(n+1, vector<int>(n+1, 0));
    cout << "1 1 " << n << " " << n << "\n"; fflush(stdout);
    cin >> C[n][n];
    for(int i = 1; i < n; i++) {
        if(i*2 <= n) {
            cout << i+1 << " 1 " << n << " " << n << "\n"; fflush(stdout);
            cin >> C[i][n];
            C[i][n] = C[n][n] - C[i][n];
            cout << "1 " << i+1 << " " << n << " " << n << "\n"; fflush(stdout);
            cin >> C[n][i];
            C[n][i] = C[n][n] - C[n][i];
        } else {
            cout << "1 1 " << i << " " << n << "\n"; fflush(stdout);
            cin >> C[i][n];
            cout << "1 1 " << n << " " << i << "\n"; fflush(stdout);
            cin >> C[n][i];
        }
    }
    //cout << C;
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < n; j++) {
            pi a, b;
            bool x = (i*2 <= n), y = (j*2 <= n);
            if(x) { a.fi = i+1; b.fi = n; }
            else { a.fi = 1; b.fi = i; }
            if(y) { a.se = j+1; b.se = n; }
            else { a.se = 1; b.se = j; }
            cout << a.fi << " " << a.se << " " << b.fi << " " << b.se << "\n"; fflush(stdout);
            int t; cin >> t;
            if(x && y) C[i][j] = t+C[n][j]+C[i][n]-C[n][n];
            else if(x) C[i][j] = C[n][j]-t;
            else if(y) C[i][j] = C[i][n]-t;
            else C[i][j] = t;
        }
    }
    //cout << C;
    cout << "END\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) cout << C[i+1][j+1]-C[i][j+1]-C[i+1][j]+C[i][j];
        cout << "\n";
    }
    fflush(stdout);
    return 0;
}