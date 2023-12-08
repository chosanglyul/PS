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
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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

pll solve(int n, int s, int e) {
    queue<piii> Q; Q.push({0, {s, -1}});
    vector<int> D(n, INF);
    vector<ll> E(n, 0LL); E[s] = 1LL;
    while(Q.size()) {
        piii tmp = Q.front(); Q.pop();
        if(tmp.se.fi < 0 || tmp.se.fi >= n || tmp.fi > D[tmp.se.fi]) continue;
        if(tmp.fi == D[tmp.se.fi]) {
            if(tmp.se.se >= 0) E[tmp.se.fi] += E[tmp.se.se];
            continue;
        } else {
            D[tmp.se.fi] = tmp.fi;
            if(tmp.se.se >= 0) E[tmp.se.fi] = E[tmp.se.se];
        }
        Q.push({tmp.fi+1, {tmp.se.fi+1, tmp.se.fi}});
        Q.push({tmp.fi+1, {tmp.se.fi-1, tmp.se.fi}});
        Q.push({tmp.fi+1, {tmp.se.fi*2, tmp.se.fi}});
    }
    return {D[e], E[e]};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    pll ans = solve(101010, n, k);
    cout << ans.fi << "\n" << ans.se << "\n";
    return 0;
}
