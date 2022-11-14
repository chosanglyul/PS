#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n; cin >> m >> n;
    vector<vector<int>> A(m, vector<int>(n)), B(m+1, vector<int>(n+1, 0));
    for(auto &i : A) for(auto &j : i) cin >> j;
    for(int i = 0; i < m; i++) for(int j = 0; j < n; j++)
        B[i+1][j+1] = B[i+1][j] + B[i][j+1] - B[i][j] + A[i][j];
    int cnt = 0;
    for(int x = 0; x < m; x++) {
        for(int y = x+1; y <= m; y++) {
            for(int s = 0, e = 0; s < n; s++) {
                while(e <= n && B[y][e] - B[y][s] - B[x][e] + B[x][s] < 10) e++;
                if(e <= n && B[y][e] - B[y][s] - B[x][e] + B[x][s] == 10) cnt++;
            }
        }
    }
    cout << cnt << "\n";
    return 0;
}