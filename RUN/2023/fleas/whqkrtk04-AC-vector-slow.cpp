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

void dfs(pii x, vector<vector<bool>> &chk, vector<vector<vector<pii>>> &E) {
    if(chk[x.fi][x.se]) return;
    chk[x.fi][x.se] = true;
    for(auto &i : E[x.fi][x.se]) dfs(i, chk, E);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<vector<char>> A(n, vector<char>(m));
    for(auto &i : A) for(auto &j : i) cin >> j;

    vector<vector<vector<pii>>> E(n, vector<vector<pii>>(m));
    for(int i = 0; i < n; i++) {
        for(int j = m-1, x = INF; j >= 0; j--) {
            if(x <= j+k) E[i][j].push_back({i, x});
            if(A[i][j] == 'L') x = j;
        }
        for(int j = 0, x = -INF; j < m; j++) {
            if(x >= j-k) E[i][j].push_back({i, x});
            if(A[i][j] == 'R') x = j;
        }
    }
    for(int j = 0; j < m; j++) {
        for(int i = n-1, y = INF; i >= 0; i--) {
            if(y <= i+k) E[i][j].push_back({y, j});
            if(A[i][j] == 'U') y = i;
        }
        for(int i = 0, y = -INF; i < n; i++) {
            if(y >= i-k) E[i][j].push_back({y, j});
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

    vector<vector<bool>> chk(n, vector<bool>(m, false));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < min(m, k); j++)
            if(A[i][j] == 'L') dfs({i, j}, chk, E);
        for(int j = max(0, m-k); j < m; j++)
            if(A[i][j] == 'R') dfs({i, j}, chk, E);
    }
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < min(n, k); i++)
            if(A[i][j] == 'U') dfs({i, j}, chk, E);
        for(int i = max(0, n-k); i < n; i++)
            if(A[i][j] == 'D') dfs({i, j}, chk, E);
    }

    int cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(chk[i][j]) cnt++;
    cout << cnt << "\n";
    return 0;
}
