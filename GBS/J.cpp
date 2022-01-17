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

void dfs(int x, int d, vector<vector<int>>& E, vector<int>& D, vector<bool>& vis) {
    if(vis[x]) return;
    vis[x] = true;
    D[x] = ++d;
    for(auto i : E[x]) dfs(i, d, E, D, vis);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n), D(n, 0);
    vector<bool> vis(n, false);
    vector<vector<int>> B(n), E(n);
    for(int i = 0; i < n; i++) {
        cin >> A[i]; A[i]--;
        E[A[i]].push_back(i);
    }
    dfs(0, 0, E, D, vis);
    for(int i = 0; i < n; i++) B[i].push_back(A[i]);
    for(int i = 1; i < 30; i++)
        for(int j = 0; j < n; j++)
            B[j].push_back(B[B[j][i-1]][i-1]);
    int q; cin >> q;
    while(q--) {
        int t; cin >> t;
        if(--t) {
            int k, x; cin >> k >> x; --x;
            if(D[x] && D[x] <= k) {
                k -= D[x], x = A[0];
                if(D[x]) k %= D[x];
            }
            for(int i = 0; i < 30; i++, k >>= 1)
                if(k&1) x = B[x][i];
            cout << x+1 << "\n";
        } else {
            int x; cin >> x;
            A[0] = --x;
        }
    }
    return 0;
}