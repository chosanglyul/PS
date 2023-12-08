#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define fi first
#define se second

vector<vector<pii>> solve(vector<int> &D, vector<int> &A) {
    int n = D.size();
    vector<vector<pii>> ret;
    for(int i = 0; i < n; i++) {
        int j = i, t = 0;
        vector<pii> T(n);
        do {
            t += D[j];
            T[j] = {t, t+A[j]};
            t += A[j];
            if((++j) >= n) { j -= n; }
        } while(j != i);
        ret.push_back(T);
    }
    return ret;
}

vector<vector<bool>> makecan(int n, vector<vector<pii>> &X, vector<vector<pii>> &Y) {
    vector<vector<bool>> AB(n, vector<bool>(n, true));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++) {
                pii x = X[i][k], y = Y[j][k];
                if(!(x.se <= y.fi || y.se <= x.fi)) {
                    AB[i][j] = false;
                    break;
                }
            }
    return AB;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<int> D(n), A(n), B(n), C(n);
    for(auto &i : D) cin >> i;
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    for(auto &i : C) cin >> i;
    
    vector<vector<pii>> X = solve(D, A), Y = solve(D, B), Z = solve(D, C);
    vector<vector<bool>> AB = makecan(n, X, Y), BC = makecan(n, Y, Z), CA = makecan(n, Z, X);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                if(AB[i][j] && BC[j][k] && CA[k][i]) {
                    cout << i+1 << " " << j+1 << " " << k+1 << "\n";
                    return 0;
                }
    cout << "impossible\n";
    return 0;
}
