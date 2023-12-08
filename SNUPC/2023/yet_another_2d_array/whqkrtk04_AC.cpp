#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define fi first
#define se second

int solve(vector<vector<int>> &A,
    int n, int m, int x, int y) {
    vector<vector<pii>> dpx(n, vector<pii>(m-y+1));
    for(int i = 0; i < n; i++) {
        deque<pii> DQmin, DQmax;
        for(int j = 0; j < y; j++) {
            while(DQmin.size() && DQmin.back().fi >= A[i][j]) DQmin.pop_back();
            DQmin.push_back({A[i][j], j+y});
            while(DQmax.size() && DQmax.back().fi <= A[i][j]) DQmax.pop_back();
            DQmax.push_back({A[i][j], j+y});
        }
        for(int j = y; j <= m; j++) {
            while(DQmin.front().se < j) DQmin.pop_front();
            while(DQmax.front().se < j) DQmax.pop_front();
            dpx[i][j-y] = {DQmin.front().fi, DQmax.front().fi};
            if(j < m) {
                while(DQmin.size() && DQmin.back().fi >= A[i][j]) DQmin.pop_back();
                DQmin.push_back({A[i][j], j+y});
                while(DQmax.size() && DQmax.back().fi <= A[i][j]) DQmax.pop_back();
                DQmax.push_back({A[i][j], j+y});
            }
        }
    }

    vector<vector<pii>> dpy(n-x+1, vector<pii>(m-y+1));
    for(int j = 0; j <= m-y; j++) {
        deque<pii> DQmin, DQmax;
        for(int i = 0; i < x; i++) {
            while(DQmin.size() && DQmin.back().fi >= dpx[i][j].fi) DQmin.pop_back();
            DQmin.push_back({dpx[i][j].fi, i+x});
            while(DQmax.size() && DQmax.back().fi <= dpx[i][j].se) DQmax.pop_back();
            DQmax.push_back({dpx[i][j].se, i+x});
        }
        for(int i = x; i <= n; i++) {
            while(DQmin.front().se < i) DQmin.pop_front();
            while(DQmax.front().se < i) DQmax.pop_front();
            dpy[i-x][j] = {DQmin.front().fi, DQmax.front().fi};
            if(i < n) {
                while(DQmin.size() && DQmin.back().fi >= dpx[i][j].fi) DQmin.pop_back();
                DQmin.push_back({dpx[i][j].fi, i+x});
                while(DQmax.size() && DQmax.back().fi <= dpx[i][j].se) DQmax.pop_back();
                DQmax.push_back({dpx[i][j].se, i+x});
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
