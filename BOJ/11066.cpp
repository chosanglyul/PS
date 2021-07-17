#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        vector<int> B(n+1, 0);
        for(int i = 1; i <= n; i++) B[i] = B[i-1]+A[i-1];
        vector<vector<int>> D(n, vector<int>(n, INF));
        for(int i = 0; i < n; i++) D[i][i] = 0;
        for(int i = 1; i < n; i++)
            for(int j = 0; j < n-i; j++)
                for(int k = j; k < i+j; k++)
                    D[j][i+j] = min(D[j][i+j], D[j][k]+B[i+j+1]-B[j]+D[k+1][i+j]);
        cout << D[0][n-1] << "\n";
    }
    return 0;
}