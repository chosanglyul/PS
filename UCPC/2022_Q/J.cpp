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
    int n; cin >> n;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    vector<ll> B(A);
    sort(B.begin(), B.end());
    vector<int> C(n);
    for(int i = 0; i < n; i++) {
        if(i && A[i-1] == A[i]) C[i] = C[i-1]+1;
        else C[i] = lower_bound(B.begin(), B.end(), A[i]) - B.begin();
    }
    for(int i = 0; i < n; i++) {
        __int128_t tmp = (__int128_t)A[i]*A[C[i]];
        __int128_t l = 0, r = LLINF;
        while(l+1 < r) {
            __int128_t mi = (l+r)/2;
            if(mi*mi <= tmp) l = mi;
            else r = mi;
        }
        if(l*l != tmp) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}