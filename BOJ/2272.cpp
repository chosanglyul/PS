#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    for(int i = 0, j = 1; i < 30; i++, j <<= 1) {
        if(m&j) {
            vector<int> B(n);
            for(int k = 0; k < n; k++) B[k] = A[(k+j)%n];
            for(int k = 0; k < n; k++) A[k] ^= B[k];
        }
    }
    for(auto i : A) cout << i << "\n";
    return 0;
}