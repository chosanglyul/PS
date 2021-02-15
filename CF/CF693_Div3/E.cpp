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

bool cmp(pii x, pii y) {
    if(x.se.fi == y.se.fi)
        return x.se.se < y.se.se;
    return x.se.fi < y.se.fi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<pii> A(n*2);
        vector<int> B(n, -1);
        for(int i = 0; i < n; i++) {
            A[i].fi = i;
            cin >> A[i].se.fi >> A[i].se.se;
            A[i+n] = A[i];
            swap(A[i+n].se.fi, A[i+n].se.se);
        }
        sort(A.begin(), A.end(), cmp);
        for(int i = 0, mi = 0, tmp = -1; i < 2*n; i++) {
            if(A[mi].se.se > A[i].se.se) {
                tmp = mi;
                mi = i;
            }
            if(A[i].se.fi == A[mi].se.fi) {
                if(tmp > -1 && A[i].se.se > A[tmp].se.se) B[A[i].fi] = A[mi].fi+1;
            } else if(A[i].se.se > A[mi].se.se) B[A[i].fi] = A[mi].fi+1;
        }
        for(auto i : B) cout << i << " ";
        cout << "\n";
    }
    return 0;
}