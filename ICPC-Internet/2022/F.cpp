#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second
const int INF = (int)1e9+5;

int dfs(int x, vector<int>& A, vector<int>& D) {
    if(A[x] == -1) return D[x] = 1;
    if(D[x] != -1) return D[x];
    return D[x] = dfs(A[x], A, D)+1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n; cin >> m >> n;
    vector<int> A(n, -1), B(n, 0), D(n, -1);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        A[x] = y;
        B[y]++;
    }
    queue<int> Q;
    for(int i = 0; i < n; i++)
        if(B[i] == 0) Q.push(i);
    while(Q.size()) {
        int tmp = Q.front(); Q.pop();
        if(A[tmp] == -1) continue;
        if(--B[A[tmp]] == 0) Q.push(A[tmp]);
    }
    for(int i = 0; i < n; i++) {
        if(B[i] > 0 && D[i] == -1) {
            int tmp = A[i], cnt = 1;
            while(tmp != i) {
                cnt++;
                tmp = A[tmp];
            }
            D[i] = cnt;
            tmp = A[i];
            while(tmp != i) {
                D[tmp] = cnt;
                tmp = A[tmp];
            }
        }
    }
    for(int i = 0; i < n; i++) dfs(i, A, D);
    int ma = 0;
    for(auto i : D) ma = max(ma, i);
    cout << ma << "\n";
    return 0;
}