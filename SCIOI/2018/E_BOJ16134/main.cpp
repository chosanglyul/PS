#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int P = 1e9+7;

ll mod(ll a, ll b) { return ((a%b) + b) % b; }

ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if (b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}

ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, r; cin >> n >> r;
    vector<ll> A(n+1), B(n+1); A[0] = 1;
    for(int i = 1; i <= n; i++)
        A[i] = (A[i-1]*i)%P;
    B[n] = inv(A[n], P);
    for(int i = n-1; i >= 0; i--)
        B[i] = (B[i+1]*(i+1))%P;
    cout << (((A[n]*B[r])%P)*B[n-r])%P << "\n";
    return 0;
}