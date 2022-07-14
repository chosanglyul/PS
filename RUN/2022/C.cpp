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

ll solve(vector<ll>& B, ll m, ll t) {
    vector<ll> A(B);
    for(auto &i : A) i += t;
    ll cnt = 0LL, cur = 0LL;
    int n = A.size();
    for(int i = 0, j = 0; i < n; cur -= A[i++]) {
        while(j < n && cur < m) cur += A[j++];
        cnt += (ll)(n-j);
        if(cur >= m) cnt++;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    ll m, k; cin >> m >> k;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    ll l = -1LL, r = m;
    while(l+1 < r) {
        ll mi = l+r>>1;
        if(solve(A, m, mi) >= k) r = mi;
        else l = mi;
    }
    cout << r << "\n";
    return 0;
}