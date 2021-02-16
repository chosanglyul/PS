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
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n), C(n, 0);
    vector<vector<int>> B(n, vector<int>());
    for(int i = 0; i < n; i++) {
        cin >> A[i];
        int x; cin >> x;
        B[i].resize(x);
        for(auto &j : B[i]) { cin >> j; j--; }
    }
    C = A;
    for(int i = 0; i < n; i++) for(auto j : B[i]) C[i] = max(C[i], A[i]+C[j]);
    int ma = 0;
    for(auto i : C) ma = max(ma, i);
    cout << ma << endl;
    return 0;
}