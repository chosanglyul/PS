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

ll getma(ll val, int x, int t) {
    return val*x+val*(val+1LL)/2LL;
}

ll getmi(ll val, int x, int t) {
    ll trn = val/t;
    return (trn*(trn+1LL)/2LL)*t+(trn+1LL)*(val-trn*t)+val*x;
}


ll search(int val, int x, int t, int gets) {
    gets -= val;
    int fl = gets/(t-1), le = gets%(t-1);
    return (ll)(val+x+1)*(x+val)/2-(ll)(x+1)*x/2+(ll)le*(x-fl+val)+(ll)(t-1)*((ll)(x+val)*(x+val+1)/2-(ll)(x+val-fl)*(x+val-fl+1)/2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int x, t, n; cin >> x >> t >> n;
        int l = 1, r = n+1;
        while(l+1 < r) {
            int mi = l+r>>1;
            if(getmi(mi, x, t) > n) r = mi;
            else l = mi;
        }
        int target = (int)min((ll)n, getma(l, x, t));
        //cout << " " << target-n << " " << l << "\n";
        int s = 1, e = l+1;
        while(s+1 < e) {
            int mi = s+e>>1;
            if(search(mi-1, x, t, l) >= target) e = mi;
            else s = mi;
        }
        cout << s << "\n";
    }
    return 0;
}