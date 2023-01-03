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

void solve(int s, int e, int js, int je, int d, vector<ll> &D, vector<ll> &T, vector<ll> &V) {
    int mi = s+e>>1, mj = -1;
    for(int i = max(js, mi-d); i <= min(je, mi); i++)
        if(mj == -1 || V[mj]-mj*T[mi] < V[i]-i*T[mi])
            mj = i;
    D[mi] = mi*T[mi]-mj*T[mi]+V[mj];
    if(s+1 == e) return;
    solve(s, mi, js, mj, d, D, T, V);
    solve(mi, e, mj, je, d, D, T, V);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d; cin >> n >> d;
    vector<ll> D(n), T(n), V(n);
    for(auto &i : T) cin >> i;
    for(auto &i : V) cin >> i;
    solve(0, n, 0, n, d, D, T, V);
    cout << *max_element(D.begin(), D.end()) << "\n";
    return 0;
}