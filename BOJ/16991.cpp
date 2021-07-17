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

double getlen(vector<pi>& A, int i, int j) {
    return sqrt((A[i].fi-A[j].fi)*(A[i].fi-A[j].fi)+(A[i].se-A[j].se)*(A[i].se-A[j].se));
}

double solve(int s, int k, int v, vector<vector<double>>& D, vector<pi>& A) {
    if(s == 0) return getlen(A, v, k);
    if(D[s][k] < INF) return D[s][k];
    for(int i = 0, j = 1; i < A.size(); i++, j <<= 1) {
        if(s&j) {
            D[s][k] = min(D[s][k], solve(s-j, i, v, D, A)+getlen(A, k, i));
        }
    }
    return D[s][k];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pi> A(n);
    vector<vector<double>> D;
    for(auto &i : A) cin >> i.fi >> i.se;
    double ans = INF;
    for(int i = 0; i < n; i++) {
        D = vector<vector<double>>(1<<n, vector<double>(n, LLINF));
        ans = min(ans, solve((1<<n)-1-(1<<i), i, i, D, A));
    }
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}