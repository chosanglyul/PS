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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, g, k; cin >> n >> g >> k;
    vector<pii> A, B;
    for(int i = 0; i < n; i++) {
        int s, l, o; cin >> s >> l >> o;
        if(o) B.push_back({s, l});
        else A.push_back({s, l});
    }
    ll l = 0LL, r = 3LL*(ll)INF;
    vector<ll> C(B.size());
    while(l+1LL < r) {
        ll mi = l+r>>1, cnt = 0LL;
        for(auto &i : A) cnt += (ll)i.fi*max(1LL, mi-i.se);
        for(int i = 0; i < B.size(); i++) C[i] = (ll)B[i].fi*max(1LL, mi-B[i].se);
        sort(C.begin(), C.end());
        for(int i = 0; i < (int)B.size()-k; i++) cnt += C[i];
        if(cnt <= g) l = mi;
        else r = mi;
    }
    cout << l << "\n";
    return 0;
}