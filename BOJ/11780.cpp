#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

void solve(int s, int e, vector<vector<int>> &B, vector<int> &V) {
    int m = B[s][e];
    if(m == -1) return;
    solve(s, m, B, V);
    V.push_back(m);
    solve(m, e, B, V);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> A(n, vector<int>(n, INF));
    vector<vector<int>> B(n, vector<int>(n, -1));
    for(int i = 0; i < n; i++) A[i][i] = 0;
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int x, y, z; cin >> x >> y >> z; --x, --y;
        A[x][y] = min(A[x][y], z);
    }

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(A[i][j] > A[i][k]+A[k][j]) {
                    A[i][j] = A[i][k]+A[k][j];
                    B[i][j] = k;
                }
            }
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(A[i][j] >= INF) {
                cout << 0 << " ";
            } else {
                cout << A[i][j] << " ";
            }
        }
        cout << "\n";
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(A[i][j] >= INF || i == j) {
                cout << 0 << "\n";
            } else {
                vector<int> V;
                solve(i, j, B, V);
                cout << V.size()+2 << " ";
                cout << i+1 << " ";
                for(auto k : V) cout << k+1 << " ";
                cout << j+1 << "\n";
            }
        }
    }
    
    return 0;
}