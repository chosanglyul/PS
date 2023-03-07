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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    cout << n*m-((n*m)%2) << "\n";
    for(int i = 1; i <= m; i++) cout << 1 << " " << i << "\n";
    if(n%2) {
        for(int j = 2; j < n-2; j += 2) {
            for(int i = m; i >= 2; i--) cout << j << " " << i << "\n";
            for(int i = 2; i <= m; i++) cout << j+1 << " " << i << "\n";
        }
        for(int i = m; i >= 2; i -= 2) {
            cout << n-1 << " " << i << "\n";
            cout << n << " " << i << "\n";
            cout << n << " " << i-1 << "\n";
            cout << n-1 << " " << i-1 << "\n";
        }
        if(m%2) cout << n-1 << " " << 1 << "\n";
        for(int j = n-2; j >= 2; j--) cout << j << " " << 1 << "\n";
    } else {
        for(int j = 2; j < n; j += 2) {
            for(int i = m; i >= 2; i--) cout << j << " " << i << "\n";
            for(int i = 2; i <= m; i++) cout << j+1 << " " << i << "\n";
        }
        for(int i = m; i >= 1; i--) cout << n << " " << i << "\n";
        for(int j = n-1; j >= 2; j--) cout << j << " " << 1 << "\n";
    }
    return 0;
}