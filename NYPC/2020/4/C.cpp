#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1e9+7;
const ll LLINF = 1e18+1;

pll dp[404][404];
pl mm[404][404];
ll pre[404];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k, x; cin >> n >> k >> x;
    cin >> pre[0];
    for(int i = 1; i < n; i++) {
        ll tmp; cin >> tmp;
        pre[i] = tmp + pre[i-1];
    }
    for(int i = 0; i < k; i++) {
        for(int j = i; j < n; j++) {
            if(i) {
                mm[i][j] = {LLINF, 0};
                dp[i][j] = {LLINF, {-1, -1}};
                for(int x = 0; x < j; x++) {
                    ll cnt = pre[j]-pre[x];
                    mm[i][j].fi = min(max(mm[i-1][x].fi, cnt), mm[i][j].fi);
                    mm[i][j].se = max(min(mm[i-1][x].se, cnt), mm[i][j].se);
                    pl inter;
                    if(dp[i-1][x].se.fi < cnt) inter = {cnt, mm[i][j].se};
                    else if(dp[i-1][x].se.se > cnt) inter = {mm[i][j].fi, cnt};
                    else inter = dp[i][j].se;
                    if(dp[i][j].fi > inter.fi-inter.se) {
                        dp[i][j].fi = inter.fi-inter.se;
                        dp[i][j].se = inter;
                    } else if(dp[i][j].fi == inter.fi-inter.se) {
                        dp[i][j].se.fi = max(inter.fi, dp[i][j].se.fi);
                        dp[i][j].se.se = min(inter.se, dp[i][j].se.se);
                    }
                }
            } else {
                mm[i][j] = {pre[j], pre[j]};
                dp[i][j] = {0LL, {pre[j], pre[j]}};
            }
        }
    }
    cout << mm[k-1][n-1].fi-mm[k-1][n-1].se << endl;
    return 0;
}