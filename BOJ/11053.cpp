#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n), B(n, 0);
    for(auto &i : A) cin >> i;
    int res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(A[j] < A[i]) B[i] = max(B[i], B[j]);
        }
        res = max(res, ++B[i]);
    }
    cout << res << "\n";
    return 0;
}