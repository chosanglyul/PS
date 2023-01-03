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
    int q; cin >> q;
    while(q--) {
        int x, t, n; cin >> x >> t >> n;
        pll ans = {LLINF, LLINF};
        vector<int> A;
        while (true) {
            A.push_back(0);
            fill(A.begin(), A.end(), 1);
            int m = n;
            for(int i = 0, y = x+1; i < A.size(); i++, y++) m -= y;
            if(m < 0) break;
            for(int i = 0, y = x+1; i < A.size(); i++, y++) {
                int tmp = min(m/y, t-A[i]);
                m -= tmp*y;
                A[i] += tmp;
            }
            reverse(A.begin(), A.end());
            ll tmp = 0LL;
            for(int i = 0, y = x+1; i < A.size(); i++, y++) tmp += (ll)y*A[i];
            ans = min(ans, {(ll)n-min((ll)n, tmp), A.size()});
        }
        cout << " " << ans.fi << "\n";
        cout << ans.se << "\n";
    }
    return 0;
}