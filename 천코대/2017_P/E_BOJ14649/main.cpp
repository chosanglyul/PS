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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int p, n; cin >> p >> n;
    vector<int> A(100), B(100);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        char c; cin >> c;
        if(c == 'R') {
            A[x] += 1;
        } else {
            A[0] += 1;
            A[--x] -= 1;
        }
    }
    B[0] = A[0];
    for(int i = 1; i < 100; i++)
        B[i] = A[i] + B[i-1];
    int cnt[3] = {0, };
    for(auto i : B)
        cnt[i%3] += 1;
    for(int i = 0; i < 3; i++)
        printf("%.2f\n", (float)cnt[i]*p/100);
    return 0;
}