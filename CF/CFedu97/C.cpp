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

int prefix[202][202];
pii dp[202][202];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int q; cin >> q;
    while(q--) {
        for(int i = 0; i < 202; i++) {
            for(int j = 0; j < 202; j++) {
                prefix[i][j] = 0;
                dp[i][j] = {INF, {-1, -1}};
            }
        }
        int n; cin >> n;
        vector<int> A(n);
        for(auto &i : A) { cin >> i; --i; }
        sort(A.begin(), A.end());
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                for(int k = i; k < n; k++) {
                    if(k == i) prefix[j][k] = abs(j-A[k]);
                    else prefix[j][k] = prefix[j][k-1]+abs(j+k-i-A[k]);
                    cout << i << " " << j << " " << k << " " << prefix[j][k] << " " << abs(j+k-i-A[k]) << "  ";
                }
                cout << "\n";
            }
            for(int j = i; j < n; j++) {
                for(int k = 0; k < n; k++) {
                    if(prefix[k][j] < dp[i][j].fi) {
                        dp[i][j].fi = prefix[k][j];
                        dp[i][j].se.fi = k;
                        dp[i][j].se.se = k+j-i;
                    }
                }
                for(int k = i+1; k <= j; k++) {
                    if(dp[i][k-1].se.se < dp[k][j].se.fi && dp[i][j].fi > dp[i][k-1].fi+dp[k][j].fi) {
                        dp[i][j].fi = dp[i][k-1].fi+dp[k][j].fi;
                        dp[i][j].se.fi = dp[i][k-1].se.fi;
                        dp[i][j].se.se = dp[k][j].se.se;
                    }
                }
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                cout << i << " " << j << " " << dp[i][j].fi << " " << dp[i][j].se.fi << " " << dp[i][j].se.se << "  ";
            }
            cout << "\n";
        }
        cout << dp[0][n-1].fi << "\n";
    }
    return 0;
}