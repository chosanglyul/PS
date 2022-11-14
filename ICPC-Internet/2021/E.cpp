#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
const int INF = (int)1e9+5;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int b, n; cin >> b >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<vector<double>> D(b, vector<double>(n, INF));
    for(int i = 0, dsu = 0, su = 0; i < n; i++) {
        dsu += A[i]*A[i];
        su += A[i];
        D[0][i] = dsu - (double)su*su/(i+1);
    }
    for(int i = 1; i < b; i++) {
        for(int j = 0; j < n; j++) {
            int dsu = 0, su = 0;
            for(int k = j-1; k >= 0; k--) {
                dsu += A[k+1]*A[k+1];
                su += A[k+1];
                double tmp = D[i-1][k] + dsu - (double)su*su/(j-k);
                D[i][j] = min(D[i][j], tmp);
            }
        }
    }
    double ans = INF;
    for(int i = 0; i < b; i++) ans = min(ans, D[i].back());
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}