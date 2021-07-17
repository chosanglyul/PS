#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<pi> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    vector<vector<int>> D(k+1, vector<int>(n, 0)), C(k+1, vector<int>(n, 0));
    for(int i = 0; i <= k; i++) {
        for(int j = 0; j < n; j++) {
            if(i) {
                C[i][j] = max(D[i][j], C[i-1][j]);
                if(j) C[i][j] = max(C[i][j], C[i][j-1]);
            } else C[i][j] = 0;
            if(i+A[j].fi > k) continue;
            if(j) D[i+A[j].fi][j] = max(D[i+A[j].fi][j], C[i][j-1]+A[j].se);
            else D[i+A[j].fi][j] = max(D[i+A[j].fi][j], A[j].se);
        }
    }
    cout << C[k].back() << "\n";
    return 0;
}