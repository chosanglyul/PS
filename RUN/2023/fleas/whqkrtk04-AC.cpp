#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef pair<pll, int> plli;
typedef pair<pli, int> plii;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;
const ll P = 998244353LL;

pii E[2020][2020][4];
bool chk[2020][2020];
const pii pINF = {-1, -1};

void dfs(pii x) {
    if(chk[x.fi][x.se]) return;
    chk[x.fi][x.se] = true;
    for(int i = 0; i < 4; i++) {
        pii tmp = E[x.fi][x.se][i];
        if(tmp != pINF) dfs(tmp);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<vector<char>> A(n, vector<char>(m));
    for(auto &i : A) for(auto &j : i) cin >> j;

    for(int i = 0; i < n; i++) {
        for(int j = m-1, x = INF; j >= 0; j--) {
            if(x <= j+k) E[i][j][0] = {i, x};
            else E[i][j][0] = pINF;
            if(A[i][j] == 'L') x = j;
        }
        for(int j = 0, x = -INF; j < m; j++) {
            if(x >= j-k) E[i][j][1] = {i, x};
            else E[i][j][1] = pINF;
            if(A[i][j] == 'R') x = j;
        }
    }
    for(int j = 0; j < m; j++) {
        for(int i = n-1, y = INF; i >= 0; i--) {
            if(y <= i+k) E[i][j][2] = {y, j};
            else E[i][j][2] = pINF;
            if(A[i][j] == 'U') y = i;
        }
        for(int i = 0, y = -INF; i < n; i++) {
            if(y >= i-k) E[i][j][3] = {y, j};
            else E[i][j][3] = pINF;
            if(A[i][j] == 'D') y = i;
        }
    }

/*
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        cout << i << " " << j << "   ";
        for(auto x : E[i][j]) cout << x.fi << " " << x.se << "  ";
        cout << endl;
    }
*/

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < min(m, k); j++)
            if(A[i][j] == 'L') dfs({i, j});
        for(int j = max(0, m-k); j < m; j++)
            if(A[i][j] == 'R') dfs({i, j});
    }
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < min(n, k); i++)
            if(A[i][j] == 'U') dfs({i, j});
        for(int i = max(0, n-k); i < n; i++)
            if(A[i][j] == 'D') dfs({i, j});
    }

    int cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(chk[i][j]) cnt++;
    cout << cnt << "\n";
    return 0;
}
