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
const ll LLINF = 1e18+1;

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
    int n; cin >> n;
    vector<vector<int>> A(n, vector<int>(n));
    for(auto &i : A) for(auto &j : i) cin >> j;
    int a = 0, b = 0;
    for(int i = 0; i < n; i++) {
        pi ta = {0, 0}, tb = {0, 0};
        for(int j = 0; j < n; j++) {
            if(j&1) {
                ta.fi += A[i][j];
                tb.fi += A[j][i];
            } else {
                ta.se += A[i][j];
                tb.se += A[j][i];
            }
        }
        a += max(ta.fi, ta.se);
        b += max(tb.fi, tb.se);
    }
    cout << max(a, b) << "\n";
    return 0;
}