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
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

ll cross(pl a, pl b) {
    return a.fi*b.se - a.se*b.fi;
}
ll cross(pl a, pl b, pl c) {
    return cross({b.fi-a.fi, b.se-a.se}, {c.fi-b.fi, c.se-b.se});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p; cin >> n >> p;
    double c = n*p/100.0;
    vector<pl> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    if(n == 1) {
        cout << "possible\n";
        return 0;
    }
    for(int _ = 0; _ < 100; _++) {
        int x = rnd(0, n-1), y = rnd(0, n-1);
        if(x == y) continue;
        int cnt = 2;
        for(int i = 0; i < n; i++) {
            if(i == x || i == y) continue;
            if(cross(A[x], A[i], A[y]) == 0LL) cnt++;
        }
        if(cnt >= c) {
            cout << "possible\n";
            return 0;
        }
    }
    cout << "impossible\n";
    return 0;
}