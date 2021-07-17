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

vector<int> solve(vector<int> A) {
    vector<int> ret;
    for(int i = 0; i < (1<<A.size()); i++) {
        int ans = 0;
        for(int j = 0, k = 1; j < A.size(); j++, k <<= 1)
            if(i & k) ans += A[j];
        ret.push_back(ans);
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s; cin >> n >> s;
    vector<int> A(n>>1), B(n-(n>>1));
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    vector<int> L = solve(A), R = solve(B);
    ll ans = 0LL;
    for(auto &i : L) ans += upper_bound(R.begin(), R.end(), s-i) - lower_bound(R.begin(), R.end(), s-i);
    if(s == 0) ans--;
    cout << ans << "\n";
    return 0;
}