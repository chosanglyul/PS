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

int lb(int x, vector<int>& A) {
    int tmp = upper_bound(A.begin(), A.end(), x) - A.begin();
    return --tmp;
}

int cost(int x) {
    if(x > 0) return x*(x+1)/2+1;
    else return 0;
}

int solve(int x, vector<int>& A, vector<int>& B) {
    if(!x) return 0;
    int ans = cost(lb(x, B));
    int bb = lb(x, A);
    return max(ans, solve(x-A[bb], A, B)+bb);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> A(1, 0), B(1, 1);
    while(A.back() < INF) A.push_back(A.back()*2+1);
    for(int i = 1; i < A.size(); i++) B.push_back(B[i-1]+A[i]);
    //cout << A << B;
    int t; cin >> t;
    while(t--) {
        int x, y; cin >> x >> y;
        int tmp = 0;
        while(x && lb(x, A) == lb(y, A)) {
            int t = lb(x, A);
            tmp += t;
            x -= A[t], y -= A[t];
        }
        int cut = lb(y, A);
        int ans = 0;
        if(x >= B[cut-1]) ans = cost(cut-1);
        else {
            int tt = x;
            while(tt) {
                int t = lb(tt, A);
                ans += t;
                tt -= A[t];
            }
        }
        //cout << tmp << " " << cut << "\n";
        //cout << ans << " " << y << "\n";
        ans = max(ans, solve(y, A, B));
        cout << tmp+ans << "\n";
    }
    return 0;
}