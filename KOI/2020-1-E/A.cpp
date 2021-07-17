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
const ll LLINF = 1e18+1;
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

vector<int> cmp(int n, vector<int> A, vector<int> B) {
    int as = 0, bs = 0;
    for(int i = 0; i < n; i++) as += A[i], bs += B[i];
    if(as == bs) {
        int i = 0;
        while(i < n && A[i] == B[i]) i++;
        if(i == n) return A;
        return A[i] > B[i] ? B : A;
    } else return as > bs ? B : A;
}

vector<int> solve(int n, int t) {
    n -= t*60;
    int sgn = 1, a = 0, b = 0;
    if(n < 0) sgn = -1, n *= -1;
    if(n%10 > 5) {
        a = n/10+1;
        b = n%10-10;
    } else {
        b = n%10;
        a = n/10;
    }
    if(sgn < 0) a *= -1, b *= -1;
    vector<int> A(5);
    A[0] = t;
    if(a > 0) A[1] = a;
    else A[2] = -a;
    if(b > 0) A[3] = b;
    else A[4] = -b;
    return A;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int t = n/60;
        if(n%60 == 0) cout << t << " 0 0 0 0\n";
        else cout << cmp(5, solve(n, t), solve(n, t+1));
    }
    return 0;
}