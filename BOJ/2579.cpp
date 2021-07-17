#include <bits/stdc++.h>
using namespace std;

int solve(int n, int m, vector<int>& A, vector<vector<int>>& D) {
    if(n <= 0) return 0;
    if(n == 1) return D[n][m] = (m == 0 ? A[0] : 0);
    if(D[n][m]) return D[n][m];
    if(m == 0) D[n][m] = max(solve(n-2, 0, A, D), solve(n-2, 1, A, D));
    else D[n][m] = solve(n-1, m-1, A, D);
    return D[n][m] = D[n][m]+A[n-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<vector<int>> D(n+1, vector<int>(2, 0));
    cout << max(solve(n, 0, A, D), solve(n, 1, A, D)) << "\n";
    return 0;
}