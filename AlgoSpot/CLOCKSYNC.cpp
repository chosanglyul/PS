#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9+1;

int solve(vector<int>& A, vector<int>& B, vector<vector<int>>& E) {
    if(E.size() == B.size()) {
        vector<int> D(A);
        for(int i = 0; i < B.size(); i++)
            for(auto j : E[i])
                D[j] += B[i];
        for(auto i : D)
            if(i%12)
                return INF;
        int ret = 0;
        for(auto i : B) ret += i/3;
        return ret;
    }
    int ret = INF;
    for(int i = 0; i < 4; i++) {
        B.push_back(i*3);
        ret = min(ret, solve(A, B, E));
        B.pop_back();
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> E = {
        {0, 1, 2},
        {3, 7, 9, 11},
        {4, 10, 14, 15},
        {0, 4, 5, 6, 7},
        {6, 7, 8, 10, 12},
        {0, 2, 14, 15},
        {3, 14, 15},
        {4, 5, 7, 14, 15},
        {1, 2, 3, 4, 5},
        {3, 4, 5, 9, 13}  
    };
    int c; cin >> c;
    while(c--) {
        vector<int> A(16), B;
        for(auto &i : A) cin >> i;
        int res = solve(A, B, E);
        if(res == INF) cout << -1 << "\n";
        else cout << res << "\n";
    }
    return 0;
}