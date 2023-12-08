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

ll squ(ll x) { return x*x; }

ll dst(plll &x, plll &y) {
    return squ(x.fi-y.fi)+squ(x.se.fi-y.se.fi)+squ(x.se.se-y.se.se);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<plll> A(n);
    for(auto &i : A) cin >> i.fi >> i.se.fi >> i.se.se;
    sort(A.begin(), A.end());
    ll misqu = LLINF;
    for(int i = 0; i < n-1; i++) misqu = min(misqu, dst(A[i], A[i+1]));
    ll ans = misqu;
    for(int i = 0; i < n; i++) {
        for(int j = i-1; j >= 0; j--) {
            if(squ(A[i].fi-A[j].fi) > misqu) break;
            ans = min(ans, dst(A[i], A[j]));
        }
        for(int j = i+1; j < n; j++) {
            if(squ(A[i].fi-A[j].fi) > misqu) break;
            ans = min(ans, dst(A[i], A[j]));
        }
    }
    cout << setprecision(20);
    cout << sqrt((double)ans) << "\n";
    return 0;
}