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

vector<int> solve(vector<vector<int>> &A, int xs, int xe, int ys, int ye) {
    vector<int> cnt(3, 0);
    bool same = true;
    for(int x = xs; x < xe; x++)
        for(int y = ys; y < ye; y++)
            same = same && A[x][y] == A[xs][ys];
    if(same) cnt[A[xs][ys]+1]++;
    else {
        vector<int> X = {xs, (xs*2+xe)/3, (xs+xe*2)/3, xe}, Y = {ys, (ys*2+ye)/3, (ys+ye*2)/3, ye};
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                vector<int> T = solve(A, X[i], X[i+1], Y[j], Y[j+1]);
                for(int k = 0; k < 3; k++) cnt[k] += T[k];
            }
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> A(n, vector<int>(n)); cin >> A;
    cout << solve(A, 0, n, 0, n) << "\n";
    return 0;
}