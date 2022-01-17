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

void pre(ll n, vector<vector<ll>>& P, vector<ll>& S) {
    if(n == 1LL) {
        P.push_back(vector<ll>());
        S.push_back(1LL);
        return;
    }
    pre(n>>1, P, S);
    vector<ll> A(P.back());
    if(!(n&1LL)) A.push_back(S.back());
    for(int i = 0; i < P.back().size(); i++)
        A.push_back(P.back()[i]+S.back()+1);
    S.push_back(S.back()*2LL+1LL);
    while(A.size() > 20000) A.pop_back();
    P.push_back(A);
}

ll solve(ll n, ll l, ll r, int k, int i, vector<vector<ll>>& P, vector<ll>& S) {
    if(l >= r) return 0LL;
    if(n == 1LL) return 1LL;
    if(r <= S[i+1]) return solve(n>>1, l, r, k, i+1, P, S);
    if(l > S[i+1]) return solve(n>>1, l-S[i+1]-1, r-S[i+1]-1, k, i+1, P, S);
    ll ans = 0LL;
    if(l == 0LL || r == S[i]) ans = solve(n>>1, 0LL, S[i+1], k, i+1, P, S);
    else {
        ll la = solve(n>>1, l, S[i+1], k, i+1, P, S);
        ll ra = solve(n>>1, 0LL, r-S[i+1]-1, k, i+1, P, S);
        ans = max(la, ra);
    }
    if(!(n&1LL)) k--;
    for(int j = 0; j <= k; j++) {
        ll la = min(P[i+1][j], S[i+1]-l);
        ll ra = min(P[i+1][k-j], r-S[i+1]-1);
        if(la < 0 || ra < 0) continue;
        ans = max(ans, la+ra+1);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n; cin >> n;
    int q; cin >> q;
    vector<vector<ll>> P;
    vector<ll> S;
    pre(n, P, S);
    reverse(P.begin(), P.end());
    reverse(S.begin(), S.end());
    for(int i = 0; i < S.size(); i++)
        while(P[i].size() <= 20000)
            P[i].push_back(S[i]);
    while(q--) {
        ll l, r; cin >> l >> r; --l;
        int k; cin >> k;
        cout << solve(n, l, r, k, 0, P, S) << "\n";
    }
    return 0;
}