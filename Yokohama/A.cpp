#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<vector<bool>>> A(n, vector<vector<bool>>(n, vector<bool>(n, true)));
    vector<vector<bool>> YZ(n, vector<bool>(n, false));
    vector<vector<bool>> ZX(n, vector<bool>(n, false));
    vector<vector<bool>> XY(n, vector<bool>(n, false));
    for(int i = n-1; i >= 0; i--) {
        for(int j = 0; j < n; j++) {
            char x; cin >> x; YZ[j][i] = (x == '1');
            if(!YZ[j][i])
                for(int k = 0; k < n; k++)
                    A[k][j][i] = false;
        }
    }
    for(int i = n-1; i >= 0; i--) {
        for(int j = 0; j < n; j++) {
            char x; cin >> x; ZX[j][i] = (x == '1');
            if(!ZX[j][i])
                for(int k = 0; k < n; k++)
                    A[i][k][j] = false;
        }
    }
    for(int i = n-1; i >= 0; i--) {
        for(int j = 0; j < n; j++) {
            char x; cin >> x; XY[j][i] = (x == '1');
            if(!XY[j][i])
                for(int k = 0; k < n; k++)
                    A[j][i][k] = false;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            bool tmp = false;
            for(int k = 0; k < n; k++)
                if(A[k][i][j]) tmp = true;
            if(tmp != YZ[i][j]) {
                cout << "No\n";
                return 0;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            bool tmp = false;
            for(int k = 0; k < n; k++)
                if(A[j][k][i]) tmp = true;
            if(tmp != ZX[i][j]) {
                cout << "No\n";
                return 0;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            bool tmp = false;
            for(int k = 0; k < n; k++)
                if(A[i][j][k]) tmp = true;
            if(tmp != XY[i][j]) {
                cout << "No\n";
                return 0;
            }
        }
    }
    cout << "Yes\n";
    return 0;
}