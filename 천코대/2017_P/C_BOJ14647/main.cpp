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
    int n, m; cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m, 0));
    int su9 = 0;
    for(auto &i : A) {
        for(auto &j : i) {
            int x; cin >> x;
            while(x) {
                if(x%10 == 9) j++, su9++;
                x /= 10;
            }
        }
    }
    int mai = -1, maj = -1;
    for(int i = 0; i < n; i++) {
        int su = 0;
        for(int j = 0; j < m; j++)
            su += A[i][j];
        if(su > mai)
            mai = su;
    }
    for(int i = 0; i < m; i++) {
        int su = 0;
        for(int j = 0; j < n; j++)
            su += A[j][i];
        if(su > maj)
            maj = su;
    }
    cout << su9-max(maj, mai);
    return 0;
}