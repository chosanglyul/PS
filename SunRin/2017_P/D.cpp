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
const int P = 1e9+7;
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

ll getsum(vector<int>& A, int s, int e) {
    ll su = 0LL;
    for(int i = s; i <= e; i++)
        su += A[i];
    return su;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    while(q--) {
        int t; cin >> t;
        if(t == 1) {
            int a, b; cin >> a >> b;
            cout << getsum(A, --a, --b) << "\n";
            swap(A[a], A[b]);
        } else {
            int a, b, c, d; cin >> a >> b >> c >> d;
            cout << getsum(A, --a, --b) - getsum(A, --c, --d) << "\n";
        }
    }
    return 0;
}