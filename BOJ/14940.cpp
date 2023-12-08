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

vector<vector<int>> bfs(int x0, int y0, vector<vector<int>>& A) {
    int n = A.size(), m = A[0].size();
    vector<vector<int>> B(n, vector<int>(m, -1));
    vector<vector<bool>> chk(n, vector<bool>(m, false));
    queue<pii> Q; Q.push({x0, y0});
    B[x0][y0] = 0; chk[x0][y0] = true;
    static const vector<pii> dxy = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while(Q.size()) {
        auto [x, y] = Q.front(); Q.pop();

        for(auto &i : dxy) {
            int xx = x+i.fi, yy = y+i.se;
            if(xx < 0 || xx >= B.size() || yy < 0 || yy >= B[xx].size()) continue;
            if(chk[xx][yy] || A[xx][yy] == 0) continue;
            chk[xx][yy] = true;
            Q.push({xx, yy});
            B[xx][yy] = B[x][y]+1;
        }
    }

    return B;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m));
    int x, y;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> A[i][j];
            if(A[i][j] == 2) x = i, y = j;
        }
    }

    vector<vector<int>> B = bfs(x, y, A);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(A[i][j] == 0) B[i][j] = 0;
    for(auto &i : B) cout << i;
    return 0;
}
