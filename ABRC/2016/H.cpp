#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int k, m, n;
pii potions[8];
int dp[101][101][256];

int solve(int e, int t, int inven) {
    // cout << e << ' ' << t << ' ' << inven << endl;
    int& ret = dp[e][t][inven];
    if (ret != -1) return ret;

    ret = 0;
    if (e > k) ret = max(ret, solve(e-k, max(0, t-m), inven) + 1);
    for (int i=0; i<n; ++i) {
        if (inven & (1 << i)) {
            int e2 = min(100, e + potions[i].first);
            int t2 = t + potions[i].second;
            if (e2 > k && t2 < 100) {
                ret = max(ret, solve(e2-k, max(0, t2-m), inven^(1<<i)) + 1);
            }
        }
    }
    return ret;
}

void solve() {
    cin >> k >> m >> n;
    for (int i=0; i<n; ++i) cin >> potions[i].first;
    for (int i=0; i<n; ++i) cin >> potions[i].second;
    memset(dp, -1, sizeof dp);
    cout << solve(100, 0, (1<<n)-1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    while (cases--) solve();

    return 0;
}