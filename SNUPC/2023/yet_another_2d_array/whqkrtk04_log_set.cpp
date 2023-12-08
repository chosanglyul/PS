#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define fi first
#define se second

int solve(vector<vector<int>> &A,
    int n, int m, int x, int y) {
    vector<vector<pii>> dpx(n, vector<pii>(m-y+1));
    for(int i = 0; i < n; i++) {
        set<pii> S;
        for(int j = 0; j < y; j++) S.insert({A[i][j], j});
        for(int j = y; j <= m; j++) {
            if(j > y) S.erase({A[i][j-y-1], j-y-1});
            dpx[i][j-y] = {S.begin()->fi, prev(S.end())->fi};
            if(j < m) S.insert({A[i][j], j});
        }
    }

    vector<vector<pii>> dpy(n-x+1, vector<pii>(m-y+1));
    for(int j = 0; j <= m-y; j++) {
        set<pii> Smi, Sma;
        for(int i = 0; i < x; i++) {
            Smi.insert({dpx[i][j].fi, i});
            Sma.insert({dpx[i][j].se, i});
        }
        for(int i = x; i <= n; i++) {
            if(i > x) {
                Smi.erase({dpx[i-x-1][j].fi, i-x-1});
                Sma.erase({dpx[i-x-1][j].se, i-x-1});
            }
            dpy[i-x][j] = {Smi.begin()->fi, prev(Sma.end())->fi};
            if(i < n) {
                Smi.insert({dpx[i][j].fi, i});
                Sma.insert({dpx[i][j].se, i});
            }
        }
    }

    int ans = 0;
    for(int i = 0; i <= n-x; i++)
        for(int j = 0; j <= m-y; j++)
            ans = max(ans, dpy[i][j].se-dpy[i][j].fi);
    return ans;
}

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> B(n, vector<int>(m));
    for(auto &i : B) for(auto &j : i) cin >> j;
    int ans = -1;
    for(int i = 1; i <= k; i++) {
        if(k%i || i > n || k/i > m) continue;
        int tmp = solve(B, n, m, i, k/i);
        ans = max(ans, tmp);
    }
    cout << ans << "\n";
    return 0;
}
