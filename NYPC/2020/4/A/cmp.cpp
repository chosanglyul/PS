#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1e9+7;
const ll LLINF = 1e18+1;

int dp[505][505];

int sol(int n, int m, int x, int y) {
    for(int i = 1; i <= n; i++) {
        dp[i][0] = INF;
        for(int j = 0; j <= i-1; j++)
            dp[i][0] = min(dp[i][0], max(dp[j][0], dp[i-1-j][0])+x);
    }
    for(int i = 1; i <= m; i++) {
        dp[0][i] = INF;
        for(int j = 0; j <= i-1; j++)
            dp[0][i] = min(dp[0][i], max(dp[0][j], dp[0][i-1-j])+y);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            dp[i][j] = min(dp[i-1][j]+x, dp[i][j-1]+y);
            int q = j;
            for(int p = 0; p <= i-1; p++) {
                while(q > 0 && dp[p][q] > dp[i-1-p][j-q]) {
                    dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-1-p][j-q])+x);
                    --q;
                }
                dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-1-p][j-q])+x);
                if(q < j) ++q;
            }
            q = j-1;
            for(int p = 0; p <= i; p++) {
                while(q > 0 && dp[p][q] > dp[i-p][j-1-q]) {
                    dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-p][j-1-q])+y);
                    --q;
                }
                dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-p][j-1-q])+y);
                if(q < j-1) ++q;
            }
        }
    }
    return dp[n][m];
}

int naive(int n, int m, int x, int y) {
    for(int i = 1; i <= n; i++) {
        dp[i][0] = INF;
        for(int j = 0; j <= i-1; j++)
            dp[i][0] = min(dp[i][0], max(dp[j][0], dp[i-1-j][0])+x);
    }
    for(int i = 1; i <= m; i++) {
        dp[0][i] = INF;
        for(int j = 0; j <= i-1; j++)
            dp[0][i] = min(dp[0][i], max(dp[0][j], dp[0][i-1-j])+y);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            dp[i][j] = min(dp[i-1][j]+x, dp[i][j-1]+y);
            for(int p = 0; p <= i-1; p++)
                for(int q = 0; q <= j; q++)
                    dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-1-p][j-q])+x);
            for(int p = 0; p <= i; p++)
                for(int q = 0; q <= j-1; q++)
                    dp[i][j] = min(dp[i][j], max(dp[p][q], dp[i-p][j-1-q])+y);
        }
    }
    return dp[n][m];
}

int randN(int n) { return (rand()%n)+1; }

int main() {
    srand((unsigned int)time(NULL));
    int N, M, X, Y; cin >> N >> M >> X >> Y;
    while(1) {
        int n = randN(N), m = randN(M), x = randN(X), y = randN(Y);
        if(x > y) {
            swap(n, m);
            swap(x, y);
        }
        if(naive(n, m, x, y) != sol(n, m, x, y)) {
            cout << n << " " << m << " " << x << " " << y << endl;
            cout << naive(n, m, x, y) << endl;
            for(int i = 0; i <= n; i++) {
                for(int j = 0; j <= m; j++) cout << dp[i][j] << " ";
                cout << endl;
            }
            cout << sol(n, m, x, y) << endl;
            for(int i = 0; i <= n; i++) {
                for(int j = 0; j <= m; j++) cout << dp[i][j] << " ";
                cout << endl;
            }
            return 0;
        }
    }
}