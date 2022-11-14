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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    sort(A.begin(), A.end());
    int p = 0, q = 0;
    while(p < n && A[p] == 0) p++;
    while(p+q < n && A[p+q] == 1) q++;
    if(p+q < n) {
        vector<int> B(A.begin()+p+q, A.end());
        int tmp;
        bool zero = (p%2 == 1 && q == 0);
        if(zero) {
            auto iter = min_element(B.begin(), B.end());
            tmp = *iter;
            B.erase(iter);
        }
        int m = B.size();
        if(m >= 2 && B[m-2] == 2 && B[m-1] == 3) swap(B[m-2], B[m-1]);
        for(int i = 0; i < m; i++) cout << B[i] << "\n";
        if(zero) cout << tmp << "\n";
    }
    for(int i = 0; i < q; i++) cout << 1 << "\n";
    for(int i = 0; i < p; i++) cout << 0 << "\n";
    return 0;
}