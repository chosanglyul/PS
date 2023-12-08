#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9+5;
int DP[5050][5050], opt[5050][5050];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n+1, 0);
        for(int i = 0; i < n; i++) {
            int x; cin >> x;
            A[i+1] = A[i]+x;
        }
        for(int i = 0; i < n; i++) {
            DP[i][i+1] = 0LL;
            opt[i][i+1] = i;
        }
        for(int i = n-1; i >= 0; i--) {
            for(int j = i+2; j <= n; j++) {
                DP[i][j] = INF;
                for(int k = opt[i][j-1]; k <= opt[i+1][j]; k++) {
                    int tmp = DP[i][k]+DP[k][j];
                    if(DP[i][j] > tmp) DP[i][j] = tmp, opt[i][j] = k;
                }
                DP[i][j] += A[j]-A[i];
            }
        }
        cout << DP[0][n] << "\n";
    }
    return 0;
}