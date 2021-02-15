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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<int> A(n), B(m);
        for(auto &i : A) { cin >> i; --i; }
        sort(A.begin(), A.end());
        int mon = 0;
        for(int i = 0; i < n; i++) mon = max(mon, i-A[i]);
        for(auto &i : B) cin >> i;
        while(mon < n && (B[n-mon-1] > B[A[mon]])) mon++;
        ll su = 0LL;
        for(int i = 0; i < mon; i++) su += B[A[i]];
        for(int i = 0; i < n-mon; i++) su += B[i];
        cout << su << "\n";
    }
    return 0;
}