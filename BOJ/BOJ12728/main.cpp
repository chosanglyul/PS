#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
typedef vector<vector<int>> vvi;
#define fi first
#define se second

vvi matmul(vvi& A, vvi& B) {
    vvi C = {{0, 0}, {0, 0}};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++)
                C[i][j] += A[i][k]*B[k][j];
            C[i][j] %= 1000;
        }
    }
    return C;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    for(int k = 0; k < t; k++) {
        vvi A = {{6, -4}, {1, 0}};
        vvi ans = {{1, 0}, {0, 1}};
        int n; cin >> n;
        while(n) {
            if(n&1) ans = matmul(A, ans);
            A = matmul(A, A);
            n >>= 1;
        }
        cout << "Case #" << k+1 << ": ";
        cout.width(3);
        cout.fill('0');
        cout << ((6*ans[1][0]+2*ans[1][1]-1)%1000+1000)%1000;
        cout << "\n";
    }
    return 0;
}