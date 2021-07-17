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
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

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

int dfs(int x, int d, int p, vector<vector<int>>& E, vector<int>& D, vector<int>& S, vector<int>& P, vector<bool>& vis) {
    if(vis[x]) return 0;
    vis[x] = true;
    D[x] = d;
    P[x] = p;
    int ret = 1;
    for(auto i : E[x]) ret += dfs(i, d+1, x, E, D, S, P, vis);
    return S[x] = ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> D(n), S(n), P(n);
    vector<bool> vis(n, false);
    vector<vector<int>> E(n);
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y; x--, y--;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    dfs(0, 0, -1, E, D, S, P, vis);
    //cout << " " << E << D << S << P;
    ll dsum = 0LL, tmp = 0LL;
    for(auto i : D) dsum += i;
    //cout << dsum << "\n";
    for(int i = 0; i < n; i++) {
        ll ssum = 0LL, sqsum = 0LL;
        for(auto j : E[i]) {
            if(j == P[i]) continue;
            ssum += S[j];
            sqsum += (ll)S[j]*S[j];
        }
        //cout << ssum << " " << sqsum << " ";
        tmp += D[i]*(2*ssum+(ssum*ssum-sqsum));
        //cout << tmp << "\n";
    }
    cout << dsum*(n-1)-tmp/2 << "\n";
    return 0;
}