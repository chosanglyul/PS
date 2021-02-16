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

void solve(vector<pi>& A, int i, int j) {
    if(A[j].fi > A[i].fi+1) {
        A[j].fi = A[i].fi+1;
        A[j].se = i;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pi> A((n+1)*3, {INF, -1});
    A[1] = {0, 1};
    for(int i = 1; i <= n; i++) {
        solve(A, i, 3*i);
        solve(A, i, 2*i);
        solve(A, i, 1+i);
    }
    cout << A[n].fi << endl;
    int bt = n;
    while(bt > 1) {
        cout << bt << " ";
        bt = A[bt].se;
    }
    cout << "1\n";
    return 0;
}