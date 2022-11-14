#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int MAX_S = 100 + 1;
int dp[MAX_S][MAX_S][MAX_S];
int dp2[MAX_S][MAX_S][MAX_S];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B, C;
    cin >> A >> B >> C;
    for (int i=0; i<=A; ++i) {
        for (int j=0; j<=B; ++j) {
            for (int k=0; k<=C; ++k) {
                dp[i][j][k] = 2*max({i,j,k}) + 2*min({i,j,k}) - (i+j+k);
            }
        }
    }

    for (int n=99; n>=1; --n) {
        for (int i=0; i<=A; ++i) {
            for (int j=0; j<=B; ++j) {
                for (int k=0; k<=C; ++k) {
                    int a = max(i-n, 0);
                    int b = max(j-n, 0);
                    int c = max(k-n, 0);
                    dp2[i][j][k] = (i+j+k) - min({dp[a][j][k], dp[i][b][k], dp[i][j][c]});
                }
            }
        }
        for (int i=0; i<=A; ++i) {
            for (int j=0; j<=B; ++j) {
                for (int k=0; k<=C; ++k) {
                    dp[i][j][k] = dp2[i][j][k];
                }
            }
        }
    }
    int diff = 2 * dp[A][B][C] - (A+B+C);
    if (diff > 0) cout << 'F';
    else if (diff == 0)  cout << 'D';
    else cout << 'S';

    return 0;
}