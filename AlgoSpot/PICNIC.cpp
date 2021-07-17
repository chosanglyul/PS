#include <bits/stdc++.h>
using namespace std;

int solve(vector<bool>& chk, vector<vector<int>>& A) {
    for(int i = 0; i < chk.size(); i++) {
        if(!chk[i]) {
            int ret = 0;
            chk[i] = true;
            for(auto j : A[i]) {
                if(chk[j]) continue;
                chk[j] = true;
                ret += solve(chk, A);
                chk[j] = false;
            }
            chk[i] = false;
            return ret;
        }
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int c; cin >> c;
    while(c--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> A(n);
        vector<bool> chk(n, false);
        for(int i = 0; i < m; i++) {
            int x, y; cin >> x >> y;
            if(x > y) swap(x, y);
            A[x].push_back(y);
        }
        cout << solve(chk, A) << "\n";
    }
    return 0;
}