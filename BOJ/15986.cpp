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

int fin(int i, vector<vector<ll>>& B) {
    int n = B.size(), m = B[i].size(); m--;
    ll tmp = 0LL;
    for(int j = m, k = 1<<m; j >= 0; j--, k >>= 1) {
        if(__gcd(B[i][j], tmp) > 1) {
            tmp = __gcd(B[i][j], tmp);
            i = (i+k)%n;
        }
    }
    return (i+1)%n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int mm = 20, n; cin >> n;
    vector<ll> A(n);
    ll t = 0LL;
    for(auto &i : A) {
        cin >> i;
        t = __gcd(t, i);
    }
    if(t > 1) {
        for(int i = 0; i < n; i++) cout << 0 << "\n";
        return 0;
    }
    vector<vector<ll>> B(n);
    for(int i = 0; i < n; i++)
        B[i].push_back(A[i]);
    for(int j = 1, k = 1; j < mm; j++, k <<= 1)
        for(int i = 0; i < n; i++)
            B[i].push_back(__gcd(B[i][j-1], B[(i+k)%n][j-1]));
    vector<int> D(n);
    for(int i = 0; i < n; i++) D[i] = fin(i, B);
    //cout << D;
    vector<vector<ll>> C(n);
    for(int i = 0; i < n; i++) {
        if(D[i] > i) C[i].push_back(D[i]-i);
        else C[i].push_back(D[i]-i+n);
    }
    for(int j = 1, k = 2; j < mm; j++, k <<= 1)
        for(int i = 0; i < n; i++)
            C[i].push_back(C[i][j-1] + C[(C[i][j-1]+i)%n][j-1]);
    //cout << C;
    for(int i = 0; i < n; i++) {
        int x = i, ma = mm-1, su = 0, cnt = 0;
        for(int j = ma, k = 1<<ma; j >= 0; j--, k >>= 1) {
            if(su + C[x][j] <= n) {
                su += C[x][j];
                x = (x+C[x][j])%n;
                cnt += k;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}