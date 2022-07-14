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

vector<pl> solve(vector<ll>& A, ll m) {
    vector<pl> R;
    for(auto i : A) {
        ll cnt = 1LL;
        while(!(i%m)) {
            cnt *= m;
            i /= m;
        }
        if(R.empty() || R.back().fi != i) R.push_back({i, cnt});
        else R.back().se += cnt;
    }
    return R;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        ll n, m; cin >> n >> m;
        vector<ll> A(n);
        for(auto &i : A) cin >> i;
        ll k; cin >> k;
        vector<ll> B(k);
        for(auto &i : B) cin >> i;
        vector<pl> C = solve(A, m);
        vector<pl> D = solve(B, m);
        bool can = (C.size() == D.size());
        for(int i = 0; i < min(C.size(), D.size()); i++)
            if(C[i] != D[i]) can = false;
        cout << (can ? "Yes" : "No") << "\n";
    }
    return 0;
}