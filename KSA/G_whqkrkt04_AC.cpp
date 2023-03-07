#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 998244353;
int mod(int a, int b) { return ((a%b)+b)%b; }

typedef vector<int> v;
typedef vector<v> vv;
typedef vector<vv> vvv;
typedef vector<vvv> vvvv;

void cal_pre(int n, int m, int x, int y, pii d, vv &pre, vv &su, vv &dp, vv &chk) {
    int xx = x+d.fi, yy = y+d.se;
    while(xx >= 0 && xx < n && yy >= 0 && yy < m) {
        if(chk[xx][yy]) pre[xx][yy] = 0;
        else pre[xx][yy] = mod(pre[xx-d.fi][yy-d.se]+su[xx-d.fi][yy-d.se]-dp[xx-d.fi][yy-d.se], P);
        xx += d.fi, yy += d.se;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<pii> d = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    vvvv dp(k+1, vvv(d.size(), vv(n, v(m, 0))));
    vvv su(k+1, vv(n, v(m, 0)));
    vv chk(n, v(m));
    for(auto &i : chk) for(auto &j : i) {
        char c; cin >> c;
        j = (c == '#');
    }
    int r, c;
    cin >> r >> c; --r, --c;
    su[0][r][c] = 1;
    for(int i = 1; i <= k; i++) {
        for(int j = 0; j < d.size(); j++) {
            vv pre(n, v(m, 0));
            bool U = d[j].fi > 0, D = d[j].fi < 0;
            bool L = d[j].se > 0, R = d[j].se < 0;
            if(U) for(int y = 0; y < m; y++) cal_pre(n, m, 0, y, d[j], dp[i][j], su[i-1], dp[i-1][j], chk);
            if(D) for(int y = 0; y < m; y++) cal_pre(n, m, n-1, y, d[j], dp[i][j], su[i-1], dp[i-1][j], chk);
            if(L) {
                for(int x = 0; x < n; x++) {
                    if(x == 0 && U) continue;
                    if(x == n-1 && D) continue;
                    cal_pre(n, m, x, 0, d[j], dp[i][j], su[i-1], dp[i-1][j], chk);
                }
            }
            if(R) {
                for(int x = 0; x < n; x++) {
                    if(x == 0 && U) continue;
                    if(x == n-1 && D) continue;
                    cal_pre(n, m, x, m-1, d[j], dp[i][j], su[i-1], dp[i-1][j], chk);
                }
            }
        }
        for(int j = 0; j < d.size(); j++)
            for(int x = 0; x < n; x++)
                for(int y = 0; y < m; y++)
                    su[i][x][y] = (su[i][x][y]+dp[i][j][x][y])%P;
    }
    cin >> r >> c; --r, --c;
    cout << su[k][r][c] << "\n";
    return 0;
}