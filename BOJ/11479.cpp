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
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    int n = s.size();
    vector<int> SA, R;
    for(int i = 0; i < n; i++) {
        SA.push_back(i);
        R.push_back(s[i] - 'a');
    }
    for(int d = 1; d < n; d <<= 1) {
        auto cmp = [&](int a, int b) {
            if(R[a] != R[b]) return R[a] < R[b];
            return (a+d < n && b+d < n) ? (R[a+d] < R[b+d]) : (a > b);
        };
        sort(SA.begin(), SA.end(), cmp);
        vector<int> T(n, 0);
        for(int i = 1; i < n; i++) T[i] = T[i-1] + cmp(SA[i-1], SA[i]);
        for(int i = 0; i < n; i++) R[SA[i]] = T[i];
    }
    vector<int> LCP(n-1, 0);
    for(int i = 0, j = 0; i < n; i++, j = max(j-1, 0)) {
        if(R[i] == n-1) continue;
        while(s[i+j] == s[SA[R[i]+1]+j]) j++;
        LCP[R[i]] = j;
    }
    ll ans = (ll)n*(n+1)/2LL;
    for(auto i : LCP) ans -= i;
    cout << ans << "\n";
    return 0;
}