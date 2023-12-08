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

void solve(int s, int e, vector<int> &A) {
    if(s >= e) return;
    if(s+1 < e) {
        int l = s+1, r = e;
        while(l+1 < r) {
            int mi = l+r>>1;
            if(A[mi] < A[s]) l = mi;
            else r = mi;
        }
        // cout << s << " " << e << " " << l+1 << "\n";
        if(A[s] < A[s+1]) {
            solve(s+1, e, A);
        } else {
            solve(s+1, l+1, A);
            solve(l+1, e, A);
        }
    }
    cout << A[s] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int x;
    vector<int> A;
    while(cin >> x) A.push_back(x);
    solve(0, A.size(), A);
    return 0;
}
