#include <bits/stdc++.h>
using namespace std;

int p[101010][20];
vector<int> A[101010];
bool vis[101010];
int depth[101010];

void dfs(int i, int d) {
    vis[i] = true;
    depth[i] = d;
    for(int j = 1; j < 20; j++)
        p[i][j] = p[p[i][j-1]][j-1];
    for(auto &j : A[i]) {
        if(!vis[j]) {
            p[j][0] = i;
            dfs(j, d+1);
        }
    }
}

int lca(int x, int y) {
    if(depth[x] < depth[y]) swap(x, y);
    for(int i = 19; i >= 0; i--)
        if(depth[p[x][i]] >= depth[y])
            x = p[x][i];
    if(x == y) return x;
    for(int i = 19; i >= 0; i--)
        if(p[x][i] != p[y][i])
            x = p[x][i], y = p[y][i];
    return p[x][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        --x, --y;
        A[x].push_back(y);
        A[y].push_back(x);
    }
    dfs(0, 0);
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        cout << lca(--x, --y)+1 << "\n";
    }
    return 0;
}
