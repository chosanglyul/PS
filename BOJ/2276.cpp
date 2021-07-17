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

int m, n;
vector<pi> d = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<vector<int>> A, C;
vector<vector<bool>> B, vis;
priority_queue<pii, vector<pii>, greater<pii>> Q;

void dfs(int x, int y, int h) {
    if(x < 0 || x >= m || y < 0 || y >= n) return;
    if(B[x][y] || vis[x][y]) return;
    if(A[x][y] > h) {
        Q.push({A[x][y], {x, y}});
        B[x][y] = true;
    } else {
        vis[x][y] = true;
        C[x][y] = h-A[x][y];
        for(auto &i : d) dfs(x+i.fi, y+i.se, h);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n; swap(m, n);
    if(n == 1 || m == 1) { cout << 0 << "\n"; return 0; }

    A = vector<vector<int>>(m, vector<int>(n));
    C = vector<vector<int>>(m, vector<int>(n));
    B = vector<vector<bool>>(m, vector<bool>(n, false));
    vis = vector<vector<bool>>(m, vector<bool>(n, false));
    for(auto &i : A) for(auto &j : i) cin >> j;
    //cout << " " << A;
    
    for(int i = 0; i < m-1; i++) Q.push({A[i][0], {i, 0}}), B[i][0] = true;
    for(int i = 0; i < n-1; i++) Q.push({A[m-1][i], {m-1, i}}), B[m-1][i] = true;
    for(int i = m-1; i > 0; i--) Q.push({A[i][n-1], {i, n-1}}), B[i][n-1] = true;
    for(int i = n-1; i > 0; i--) Q.push({A[0][i], {0, i}}), B[0][i] = true;

    while(Q.size()) {
        pii tmp = Q.top(); Q.pop();
        //cout << tmp.fi << "   " << tmp.se << "\n";
        for(auto &i : d) dfs(tmp.se.fi+i.fi, tmp.se.se+i.se, tmp.fi);
    }

    ll ans = 0;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(B[i][j]) continue;
            ans += C[i][j];
        }
    }
    cout << ans << "\n";
    return 0;
}