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
const int MOD = 1e9 + 7;

int solve(vector<pii> arr) {
    int n = (int)arr.size() - 1;
    // for (int i=1; i<=n; ++i) cout << arr[i].first << ' ' << arr[i].second << endl;
    n /= 2;
    array<vector<ll>, 2> dp;
    dp[0] = dp[1] = vector<ll>(n+1);
    
    int cur = 0;
    dp[cur][0] = 1;
    fill(dp[cur].begin()+1, dp[cur].end(), 0);
    vector<int> ps(2*n+1, 0);
    for (int i=1; i<=2*n; ++i) ps[i] = ps[i-1] + (arr[i].first == 0 ? 1 : -1);
    for (int i=1; i<=2*n; ++i) {
        if (arr[i].first == 0) {
            if (arr[i].second == 0) {
                dp[cur^1] = dp[cur];
                // cout << i << endl;
                for (int j=0; j<=n; ++j) dp[cur^1][j] = dp[cur][j];
            } else {
                dp[cur^1][0] = 0;
                for (int k=1; k<=n; ++k) dp[cur^1][k] = dp[cur][k-1];
            }
        } else {
            if (arr[i].second == 0) {
                for (int k=0; k<=n; ++k) {
                    dp[cur^1][k] = dp[cur][k] * (ps[i-1]-k) % MOD;
                    if (k < n) dp[cur^1][k] += dp[cur][k+1] * (k+1) % MOD;
                    dp[cur^1][k] %= MOD;
                }
            } else {
                for (int k=0; k<=n; ++k) {
                    dp[cur^1][k] = dp[cur][k] * (ps[i-1]-k) % MOD;
                }
            }
        }
        cur ^= 1;
        //cout << i << endl;
        //for (int j=0; j<=n; ++j) cout << dp[cur][j] << ' ';
        //cout << endl;
    }
    return dp[0][0] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pii> arr(2*n+1);
    for (int i=1; i<=2*n; ++i) {
        char ch; int x;
        cin >> ch >> x;
        if (ch == 'I') {
            arr[i] = { 0, x };
        } else {
            arr[i] = { 1, x };
        }
    }

    vector<int> already_paired(n+1, 0);
    for (int i=1; i<=2*n; ++i) {
        if (arr[i].second != 0) already_paired[arr[i].second]++;
    }
    
    int accum = 0;
    vector<vector<pii>> decompose(1);
    decompose[0].resize(1);
    for (int i=1; i<=2*n; ++i) {
        if (already_paired[arr[i].second] < 2) {
            // cout << i << endl;
            decompose.back().push_back(arr[i]);
            accum += (arr[i].first == 0 ? 1 : -1);
            if (accum == 0) {
                decompose.push_back(vector<pii>(1));
            }
        }
    }

    ll ans = 1;
    for (auto& v: decompose) ans = ans * solve(v) % MOD;
    int unnamed_cnt = count(already_paired.begin()+1, already_paired.end(), 0);
    for (int i=1; i<=unnamed_cnt; ++i) {
        ans = ans * i % MOD;
    }
    cout << ans;

    return 0;
}