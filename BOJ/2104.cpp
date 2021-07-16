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

ll solve(vector<ll>& A, int l, int r) {
    if(l+1 == r) return A[l]*A[l];
    int m = l+r>>1;
    ll ans = max(solve(A, l, m), solve(A, m, r));
    int s = m-1, e = m+1;
    ll su = A[m-1]+A[m], mi = min(A[m-1], A[m]);
    ans = max(su*mi, ans);
    while(l < s && e < r) {
        if(A[s-1] > A[e]) {
            su += A[--s];
            mi = min(mi, A[s]);
        } else {
            su += A[e];
            mi = min(mi, A[e++]);
        }
        ans = max(su*mi, ans);
    }
    while(e < r) {
        su += A[e];
        mi = min(mi, A[e++]);
        ans = max(su*mi, ans);
    }
    while(l < s) {
        su += A[--s];
        mi = min(mi, A[s]);
        ans = max(su*mi, ans);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    cout << solve(A, 0, n) << "\n";
    return 0;
}