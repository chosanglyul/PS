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

void dfs(int x, int y, vector<vector<int>> &A) {
    if(x < 0 || x >= A.size() || y < 0 || y >= A[x].size() || A[x][y] != 0) return;
    A[x][y] = 2;
    dfs(x+1, y, A), dfs(x-1, y, A), dfs(x, y+1, A), dfs(x, y-1, A);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m)); cin >> A;
    for(int i = 0; i < n; i++) A[i][0] = A[i][m-1] = 2;
    for(int j = 0; j < m; j++) A[0][j] = A[n-1][j] = 2;
    for(int t = 0; ; t++) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(A[i][j] == 2)
                    dfs(i+1, j, A), dfs(i-1, j, A), dfs(i, j+1, A), dfs(i, j-1, A);
        vector<pii> tmp;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(A[i][j] != 1) continue;
                if((A[i-1][j] == 2)+(A[i][j-1] == 2)+(A[i+1][j] == 2)+(A[i][j+1] == 2) >= 2)
                    tmp.push_back({i, j});
            }
        }
        if(tmp.size()) {
            for(auto [i, j] : tmp) A[i][j] = 0;
        } else {
            cout << t;
            break;
        }
        //cout << " " << A;
    }
    return 0;
}