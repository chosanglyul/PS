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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, c; cin >> n >> c;
    if(!c) {
        cout << "0 1 0\n";
        return 0;
    }
    int xx = 0, yy = 0;
    if(n <= 63) {
        ll x = (1LL<<(n-1))-(n%2LL), y = (1LL<<(n-1))-2+(n%2LL);
        while(y && c%y == 0LL) {
            c /= y;
            yy++;
        }
        while(x && c%x == 0LL) {
            c /= x;
            xx++;
        }
    }
    if(c != 1LL || xx+yy > 31) {
        cout << -1 << "\n";
        return 0;
    }
    cout << (1<<(xx+yy))-1 << " ";
    cout << 0 << " ";
    cout << (1<<xx)-1 << "\n";
    return 0;
}