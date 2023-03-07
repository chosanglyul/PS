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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, s, k; cin >> r >> s >> k;
    vector<vector<char>> A(r, vector<char>(s)); cin >> A;
    int ans = 0, xx = 0, yy = 0;
    for(int i = 0; i+k <= r; i++) {
        for(int j = 0; j+k <= s; j++) {
            int cnt = 0;
            for(int x = 1; x < k-1; x++)
                for(int y = 1; y < k-1; y++)
                    cnt += A[i+x][j+y] == '*';
            if(cnt > ans) {
                ans = cnt;
                xx = i, yy = j;
            }
        }
    }
    A[xx][yy] = A[xx+k-1][yy] = A[xx][yy+k-1] = A[xx+k-1][yy+k-1] = '+';
    for(int x = 1; x < k-1; x++) A[xx+x][yy] = A[xx+x][yy+k-1] = '|';
    for(int y = 1; y < k-1; y++) A[xx][yy+y] = A[xx+k-1][yy+y] = '-';
    cout << ans << "\n";
    for(auto &i : A) {
        for(auto j : i) cout << j;
        cout << "\n";
    }
    return 0;
}