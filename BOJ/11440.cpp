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

typedef vector<vector<ll>> M;
typedef vector<ll> V;

int get1(M& a) { return a.size(); }
int get2(M& a) { return a[0].size(); }

M mm(M& A, M& B) {
    if(get2(A) != get1(B)) exit(1);
    M C(get1(A), V(get2(B), 0));
    for(int i = 0; i < get1(A); i++)
        for(int j = 0; j < get2(B); j++)
            for(int k = 0; k < get2(A); k++)
                C[i][j] = mod(C[i][j]+A[i][k]*B[k][j], P);
    return C;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n; cin >> n;
    M T = {{1, 1}, {1, 0}}, A = {{1, 0}, {0, 1}};
    while(n) {
        if(n&1) A = mm(T, A);
        n >>= 1;
        T = mm(T, T);
    }
    cout << mod(A[0][0]*A[1][0], P) << "\n";
    return 0;
}