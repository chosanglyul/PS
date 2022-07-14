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
    cout << "+ 6 4 6\n"; fflush(stdout);
    cout << "+ 8 2 8\n"; fflush(stdout);
    cout << "< 4 2\n"; fflush(stdout);
    int x; cin >> x;
    if(x == 0) {
        cout << "< 1 3\n"; fflush(stdout);
        int y; cin >> y;
        cout << "! " << y << "\n"; fflush(stdout);
        return 0;
    }
    if(x > 0) { // D > B
        cout << "+ 11 4 9\n"; fflush(stdout);
        cout << "+ 12 2 9\n"; fflush(stdout);
    } else { // D < B
        cout << "+ 11 2 9\n"; fflush(stdout);
        cout << "+ 12 4 9\n"; fflush(stdout);
    }
    int z = 1; // X10 <- gcd(B, D)
    while(z) {
        int y = 1;
        while(y > -1) {
            cout << "- 11 11 12\n"; fflush(stdout);
            cout << "< 11 12\n"; fflush(stdout);
            cin >> y;
        }
        cout << "< 11 9\n"; fflush(stdout);
        cin >> z;
        cout << "+ 13 11 9\n"; fflush(stdout);
        cout << "+ 11 12 9\n"; fflush(stdout);
        cout << "+ 12 13 9\n"; fflush(stdout);
    }
    cout << "+ 10 11 9\n"; fflush(stdout);
    z = 1; // FOR D
    while(z) {
        cout << "+ 5 1 5\n"; fflush(stdout);
        cout << "- 6 6 10\n"; fflush(stdout);
        cout << "< 6 9\n"; fflush(stdout);
        cin >> z;
    }
    z = 1; // FOR B
    while(z) {
        cout << "+ 7 3 7\n"; fflush(stdout);
        cout << "- 8 8 10\n"; fflush(stdout);
        cout << "< 8 9\n"; fflush(stdout);
        cin >> z;
    }
    cout << "< 5 7\n"; fflush(stdout);
    cin >> z;
    cout << "! " << z << "\n"; fflush(stdout);
    return 0;
}