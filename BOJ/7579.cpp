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
    int n, m, suc = 0; cin >> n >> m;
    vector<int> A(n), B(n);
    for(auto &i : A) cin >> i;
    for(auto &i : B) {
        cin >> i;
        suc += i;
    }
    vector<vector<int>> dp(n, vector<int>(suc+1, 0));
    for(int i = 0; i < n; i++) {
        if(i) dp[i] = dp[i-1];
        for(int j = 0; j <= suc; j++) {
            if(j-B[i] < 0) continue;
            if(i) dp[i][j] = max(dp[i][j], dp[i-1][j-B[i]]+A[i]);
            else dp[i][j] = max(dp[i][j], A[i]);
        }
    }
    /*
    for(auto &i : dp) {
        for(auto j : i)
            cout << j << " ";
        cout << endl;
    }
    */
    for(int i = 0; i <= suc; i++) {
        for(int j = 0; j < n; j++) {
            if(dp[j][i] >= m) {
                cout << i << endl;
                return 0;
            }
        }
    }
    return 0;
}