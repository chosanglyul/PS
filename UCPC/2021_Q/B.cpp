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

vector<pii> d = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int x, int y, vector<vector<int>> &C, int a, int b) {
    if(x < 0 || x >= C.size() || y < 0 || y >= C[x].size() || C[x][y] != a) return;
    C[x][y] = b;
    for(auto &[i, j]: d) dfs(x+i, y+j, C, a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m)),
        B(n, vector<int>(m)), C(n, vector<int>(m));
    for(auto &i : A) for(auto &j : i) cin >> j;
    for(auto &i : B) for(auto &j : i) cin >> j;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            C[i][j] = (A[i][j] != B[i][j]);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(C[i][j]) {
                dfs(i, j, A, A[i][j], B[i][j]);
                goto end;
            }
        }
    }
end:
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(A[i][j] != B[i][j]) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    cout << "YES\n";
    return 0;
}