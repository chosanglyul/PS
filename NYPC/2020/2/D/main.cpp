#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef pair<pi, pi> pii;
#define fi first
#define se second

char M[1010][1010];
bool visit[1010][1010];
int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
int cnt = 0;

void dfs1(int x, int y) {
    if(visit[x][y] || M[x][y] == 'S') return;
    visit[x][y] = true;
    M[x][y] = 'L';
    for(int i = 0; i < 4; i++) dfs1(x+dx[i], y+dy[i]);
}

void dfs2(int x, int y, bool st) {
    if(visit[x][y] || M[x][y] != 'L') return;
    visit[x][y] = true;
    if(st) ++cnt;
    for(int i = 0; i < 4; i++) dfs2(x+dx[i], y+dy[i], false);
}

pi addi(pi a, pi b) { return {a.fi+b.fi, a.se+b.se}; }

pi dfs3(int x, int y) {
    if(M[x][y] == 'L') exit(100);
    if(visit[x][y] || M[x][y] == 'S') return {0, 0};
    visit[x][y] = true;
    pi ans = {0, 0};
    if((x+y)%2) ans.fi++;
    else ans.se++;
    for(int i = 0; i < 4; i++) ans = addi(ans, dfs3(x+dx[i], y+dy[i]));
    return ans;
}

void clearvisit(int r, int c) {
    for(int i = 0; i <= r+1; i++)
        for(int j = 0; j <= c+1; j++)
            visit[i][j] = false;
}

void solvemin(int r, int c) {
    for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++)
            if(M[i][j] == 'L')
                dfs1(i, j);
}

void solvemax(int r, int c) {
    for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++)
            if(M[i][j] == '?')
                for(int k = 0; k < 4; k++)
                    if(M[i+dx[k]][j+dy[k]] == 'L') M[i][j] = 'S';
    for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++)
            if(M[i][j] == '?') {
                pi tmp = dfs3(i, j);
                cnt += max(tmp.fi, tmp.se);
            }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int r, c; cin >> r >> c;
    string s; cin >> s;
    for(int i = 0; i <= r+1; i++) M[i][0] = M[i][c+1] = 'S';
    for(int i = 0; i <= c+1; i++) M[0][i] = M[r+1][i] = 'S';
    for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++)
            cin >> M[i][j];
    if(s == "min") solvemin(r, c);
    else solvemax(r, c);
    clearvisit(r, c);
    for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++)
            dfs2(i, j, true);
    cout << cnt << endl;
    return 0;
}