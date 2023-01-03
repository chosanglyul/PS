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

void dfs(int x, vector<vector<int>>& E, int &cnt, vector<bool>& vis, vector<pii>& A) {
    if(vis[x]) return;
    vis[x] = true;
    A[x].fi = cnt++;
    for(auto i : E[x]) dfs(i, E, cnt, vis, A);
    A[x].se = cnt++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q; cin >> n >> m >> q;
    vector<vector<int>> E(3*n);
    vector<int> I(3*n, 0);
    for(int i = 0; i < m; i++) {
        int x, y, z; cin >> x >> y; --x, --y;
        char c; cin >> c; z = c-'x';
        x += z*n, y += ((z+1)%3)*n;
        E[y].push_back(x);
        I[x]++;
    }
    vector<int> J;
    for(int i = 0; i < 3*n; i++) if(!I[i]) J.push_back(i);

    bool res = false;
    queue<int> Q;
    for(auto i : J) Q.push(i);
    while(Q.size()) {
        int tmp = Q.front(); Q.pop();
        for(auto j : E[tmp]) if(--I[j] == 0) Q.push(j);
    }
    for(int i = 0; i < 3*n; i++) if(I[i]) res = true;
    //cout << res << "\n";

    vector<pii> A(3*n);
    if(!res) {
        int cnt = 0;
        vector<bool> vis(3*n, false);
        for(auto i : J) dfs(i, E, cnt, vis, A);
    }
    //cout << A;

    for(int i = 0; i < q; i++) {
        int x, y, z; cin >> x >> y; --x, --y;
        char c; cin >> c; z = c-'x';
        x += z*n, y += ((z+1)%3)*n;
        if(res) cout << 1 << "\n";
        else {
            if(A[x].fi < A[y].fi && A[y].se < A[x].se) cout << 1 << "\n";
            else cout << 0 << "\n";
        }
    }
    return 0;
}