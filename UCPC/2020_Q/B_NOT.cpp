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

int solve(int a, int b) {
    int aa = a, bb = b;
    while(aa) {
        aa /= 10;
        bb++;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string x = "1-3-5-7-9-12-15-18-21", y = "1-3-5-7-10-13-16-19", z = "-2-4-6-8-11-14-17-20";
    int t; cin >> t;
    while(t--) {
        int a, b; cin >> a >> b;
        string s;
        switch(solve(a, b)) {
            case 0: s = x; break;
            case 1: s = y; break;
            case 2: s = z; break;
        }
        if(b >= 2 || (b == 1 && a >= 3) || a >= 21) {
            for(int i = 0; i < 17; i++) cout << s[i];
            cout << "...\n";
        } else {
            if(b == 1) a *= 10;
            for(int i = 0; i < a; i++) cout << s[i];
            cout << "\n";
        }
    }
    return 0;
}