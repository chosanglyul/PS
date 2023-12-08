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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n, p, h;
    cin >> n >> p >> h;
    p--; h--;

    ll L = 1ll << n;
    vector<int> is_moved;
    for (int i=0; i<n; ++i) {
        if (h >= L/2) {
            h = L-1-h;
            is_moved.push_back(1);
        } else {
            is_moved.push_back(0);
        }
        L /= 2;
    }
    reverse(is_moved.begin(), is_moved.end());
    // cout << is_moved;

    ll l = 0, r = (1ll << n) - 1;
    bool reversed = false;
    for (int i=0; i<n; ++i) {
        // cout << i << ' ' << l << ' ' << r << ' ' << endl;
        if (p-l >= (r-l+1) / 2) {
            l = (l+r+1) / 2;
            cout << (is_moved[i] ^ reversed ? 'R' : 'L');
        } else {
            r = l+(r-l)/2;
            cout << (!is_moved[i] ^ reversed ? 'R' : 'L');
        }
        
        if (is_moved[i]) reversed = !reversed;
    }

    return 0;
}
