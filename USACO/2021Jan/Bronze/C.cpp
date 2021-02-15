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
    int n; cin >> n;
    vector<int> A(n), B(n), C(n, 0);
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    for(int i = 0; i < n; i++) {
        for(auto &j : B)
            if(A[i] <= j) C[i]++;
    }
    sort(C.begin(), C.end());
    ll num = 1LL;
    for(int i = 0; i < n; i++) {
        C[i] -= i;
        //cout << C[i] << "\n";
        if(C[i] <= 0) {
            cout << "0\n";
            return 0;
        }
        num *= C[i];
    }
    cout << num << "\n";
    return 0;
}