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

double calc(string &X, int i, map<char, double> &M, vector<double> &D) {
    double y = M[X[i]];
    int siz = (int)X.size()-i-1;
    if(siz == 0) return y;
    double x = calc(X, i+1, M, D);
    double d = D[siz-1];
    double z = (x > y ? x-d : x+d);
    return (x+z)/2;
}

double calc_wrap(string &X) {
    vector<double> D(X.size()); D[0] = 90;
    for(int i = 1; i < X.size(); i++) D[i] = D[i-1]/2;
    map<char, double> M;
    M.insert({'E', 90.0});
    M.insert({'S', 180.0});
    M.insert({'W', 270.0});
    if(X.back() == 'W') M['N'] = 360.0;
    else M['N'] = 0.0;
    return calc(X, 0, M, D);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(20) << fixed;
    string X, Y; cin >> X >> Y;
    double x = calc_wrap(X), y = calc_wrap(Y);
    double d = abs(x-y);
    cout << min(360.0-d, d) << "\n";
    return 0;
}