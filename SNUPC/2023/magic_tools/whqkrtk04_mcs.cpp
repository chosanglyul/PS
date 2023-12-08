#include <bits/stdc++.h>
using namespace std;

void solve(int idx, int s, int e, int cnt, vector<vector<int>> &ans) {
    if(idx == ans.size()) return;
    int m = (s+e)/2;
    vector<int> &T = ans[idx];
    if(cnt != (e-s)/2)
        for(int i = m; i < e; i++)
            T.push_back(i);
    else
        for(int i = s; i < m; i++)
            T.push_back(i);

    solve(idx+1, s, m, cnt>>1, ans);
    solve(idx+1, m, e, cnt+1>>1, ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    
    int k = 0;
    while((1<<k) < n) k++;
    cout << k << "\n";

    vector<vector<int>> ans(k);
    solve(0, 0, n, n>>1, ans);

    cout << ans[0].size() << "\n";
    for(int i = 0; i < k; i++) {
        for(auto j : ans[i]) cout << j << " ";
        cout << "\n";
    }
}
