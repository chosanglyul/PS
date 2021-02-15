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

int dp[101][101][101];
pi ans[101][101][101];
bool chk[330];

void change(int& i, int& j, int& k, pi tmp) {
    --tmp.se;
    if(tmp.fi >= 1) i = min(i, tmp.se);
    if(tmp.fi >= 2) j = min(j, tmp.se);
    if(tmp.fi >= 3) k = min(k, tmp.se);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(int i = 0; i <= 100; i++) {
        for(int j = 0; j <= i; j++) {
            for(int k = 0; k <= j; k++) {
                memset(chk, false, sizeof(chk));
                for(int x = 0; x < i; x++) {
                    chk[dp[x][min(j, x)][min(k, x)]] = true;
                    if(dp[x][min(j, x)][min(k, x)] == 1) ans[i][j][k] = {3, x+1};
                }
                for(int x = 0; x < j; x++) {
                    chk[dp[i][x][min(k, x)]] = true;
                    if(dp[i][x][min(k, x)] == 1) ans[i][j][k] = {2, x+1};
                }
                for(int x = 0; x < k; x++) {
                    chk[dp[i][j][x]] = true;
                    if(dp[i][j][x] == 1) ans[i][j][k] = {1, x+1};
                }
                for(int idx = 0; idx < 330; idx++) {
                    if(!chk[idx]) {
                        dp[i][j][k] = idx;
                        break;
                    }
                }
            }
        }
    }
    int i, j, k; cin >> i >> j >> k;
    //cout << dp[k][j][i] << endl;
    if(dp[k][j][i] == 1) {
        cout << "fuck" << endl;
        exit(1);
    } else {
        while(dp[k][j][i]) {
            pi tmp = ans[k][j][i];
            cout << tmp.fi << " " << tmp.se << endl;
            change(i, j, k, tmp);
            cin >> tmp.fi >> tmp.se;
            change(i, j, k, tmp);
        }
    }
    return 0;
}