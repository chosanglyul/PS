#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5050;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m, k;
string s[MAXN];

struct dsu {
    int par[MAXN];
    void init() {
        iota(par, par + MAXN, 0);
    }
    int find(int a) {
        return par[a] = ((par[a] == a) ? a : find(par[a]));
    }
    void merge(int a, int b) {
        par[find(b)] = find(a);
    }
} d[4][MAXN];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 1; i <= m; i++) {
        d[0][i].init();
        d[2][i].init();
    }
    for (int i = 1; i <= n; i++) {
        d[1][i].init();
        d[3][i].init();
    }
    for (int i = 1; i <= n; i++) {
        int p = 0;
        for (int j = 1; j <= m; j++) {
            if (s[i - 1][j - 1] == 'R')
                p = j;
            
            d[1][i].merge(p, j);
        }
        p = m + 1;
        for (int j = m; j >= 1; j--) {
            if (s[i - 1][j - 1] == 'L')
                p = j;
            
            d[3][i].merge(p, j);
        }
    }
    for (int i = 1; i <= m; i++) {
        int p = n + 1;
        for (int j = n; j >= 1; j--) {
            if (s[j - 1][i - 1] == 'U')
                p = j;
            
            d[2][i].merge(p, j);
        }
        p = 0;
        for (int j = 1; j <= n; j++) {
            if (s[j - 1][i - 1] == 'D')
                p = j;
            
            d[0][i].merge(p, j);
        }
    }
    queue<pair<int, int>> q;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= m; j++) {
            if (i <= n && s[i - 1][j - 1] == 'U') {
                q.push({i, j});
                d[2][j].merge(i + 1, i);
            }
        }
        for (int j = 1; j <= n; j++) {
            if (i <= m && s[j - 1][i - 1] == 'L') {
                q.push({j, i});
                d[3][j].merge(i + 1, i);
            }
        }
    }
    for (int i = n; i > n - k; i--) {
        for (int j = 1; j <= m; j++) {
            if (i > 0 && s[i - 1][j - 1] == 'D') {
                q.push({i, j});
                d[0][j].merge(i - 1, i);
            }
        }
    }
    for (int i = m; i > m - k; i--) {
        for (int j = 1; j <= n; j++) {
            if (i > 0 && s[j - 1][i - 1] == 'R') {
                q.push({j, i});
                d[1][j].merge(i - 1, i);
            }
        }
    }
    int ans = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        ans += 1;
        for (int z = d[0][y].find(x); z != 0 && z >= x - k; z = d[0][y].find(z)) {
            q.push({z, y});
            d[0][y].merge(z - 1, z);
        }
        for (int z = d[2][y].find(x); z != n + 1 && z <= x + k; z = d[2][y].find(z)) {
            q.push({z, y});
            d[2][y].merge(z + 1, z);
        }
        for (int z = d[1][x].find(y); z != 0 && z >= y - k; z = d[1][x].find(z)) {
            q.push({x, z});
            d[1][x].merge(z - 1, z);
        }
        for (int z = d[3][x].find(y); z != m + 1 && z <= y + k; z = d[3][x].find(z)) {
            q.push({x, z});
            d[3][x].merge(z + 1, z);
        }
    }
    cout << ans;
    return 0;
}