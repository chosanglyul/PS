#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define fi first
#define se second

int solve(vector<vector<int>> &A,
    int n, int m, int x, int y) {
    vector<vector<pii>> dpx(n, vector<pii>(m-y+1));
    for(int i = 0; i < n; i++) {
        priority_queue<pii, vector<pii>, greater<pii>> PQmin;
        priority_queue<pii, vector<pii>, less<pii>> PQmax;
        for(int j = 0; j < y; j++) {
            PQmin.push({A[i][j], j+y});
            PQmax.push({A[i][j], j+y});
        }
        for(int j = y; j <= m; j++) {
            while(PQmin.top().se < j) PQmin.pop();
            while(PQmax.top().se < j) PQmax.pop();
            dpx[i][j-y] = {PQmin.top().fi, PQmax.top().fi};
            if(j < m) {
                PQmin.push({A[i][j], j+y});
                PQmax.push({A[i][j], j+y});
            }
        }
    }

    vector<vector<pii>> dpy(n-x+1, vector<pii>(m-y+1));
    for(int j = 0; j <= m-y; j++) {
        priority_queue<pii, vector<pii>, greater<pii>> PQmin;
        priority_queue<pii, vector<pii>, less<pii>> PQmax;
        for(int i = 0; i < x; i++) {
            PQmin.push({dpx[i][j].fi, i+x});
            PQmax.push({dpx[i][j].se, i+x});
        }
        for(int i = x; i <= n; i++) {
            while(PQmin.top().se < i) PQmin.pop();
            while(PQmax.top().se < i) PQmax.pop();
            dpy[i-x][j] = {PQmin.top().fi, PQmax.top().fi};
            if(i < n) {
                PQmin.push({dpx[i][j].fi, i+x});
                PQmax.push({dpx[i][j].se, i+x});
            }
        }
    }

/*
    for(auto i : dpy) {
        for(auto j : i) cout << j.fi << " " << j.se << "   ";
        cout << "\n";
    }
*/

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
