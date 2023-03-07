#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<ll>> vvi;
const int P = (int)1e9+7;

vvi gop(vvi a, vvi b) {
    vvi A(2);
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            A[i].push_back(0);
            for(int k = 0; k < 2; k++)
                A[i][j] = (A[i][j]+a[i][k]*b[k][j])%P;
        }
    }
    return A;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vvi I = {{1, 1}, {1, 0}};
    vvi A = {{1, 0}, {0, 1}};

    ll n; cin >> n;
    while(n) {
        if(n&1) A = gop(A, I);
        I = gop(I, I);
        n >>= 1;
    }

    cout << A[0][1] << endl;
    return 0;
}
