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
    int n, m; cin >> n >> m;
    vector<string> A(n), B(m), C;
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    for(int i = 0, j = 0; i < n && j < m;) {
        if(A[i] < B[j]) i++;
        else if(B[j] < A[i]) j++;
        else C.push_back(A[i++]);
    }
    cout << C.size() << "\n";
    for(auto &i : C) cout << i << "\n";
    return 0;
}