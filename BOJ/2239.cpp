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

vector<vector<vector<bool>>> D(3, vector<vector<bool>>(3, vector<bool>(10, false)));
vector<vector<bool>> H(9, vector<bool>(10, false)), V(9, vector<bool>(10, false));

bool solve(int x, int y, vector<vector<int>> &A) {
    if(x == 9) {
        for(auto &i : A) {
            for(auto j : i) cout << j;
            cout << "\n";
        }
        return true;
    }
    if(y == 9) return solve(x+1, 0, A);
    if(A[x][y]) return solve(x, y+1, A);

    for(int i = 1; i <= 9; i++) {
        A[x][y] = i;
        if(D[x/3][y/3][i] || H[x][i] || V[y][i]) continue;
        D[x/3][y/3][i] = H[x][i] = V[y][i] = true;
        if(solve(x, y+1, A)) return true;
        D[x/3][y/3][i] = H[x][i] = V[y][i] = false;
    }
    A[x][y] = 0;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> A(9, vector<int>(9, 0));
    for(auto &i : A) for(auto &j : i) {
        char c; cin >> c;
        j = c-'0';
    }
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(A[i][j]) D[i/3][j/3][A[i][j]] = H[i][A[i][j]] = V[j][A[i][j]] = true;
    solve(0, 0, A);
    return 0;
}
