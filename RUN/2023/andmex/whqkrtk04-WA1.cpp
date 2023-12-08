#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        int x = 0, y = 0, mex = 0;
        for(int i = 0, j = 1; i < 30; i++, j <<= 1) {
            y |= j;
            vector<int> B(n);
            for(int k = 0; k < n; k++) B[k] = A[k]&y;
            sort(B.begin(), B.end());
            B.erase(unique(B.begin(), B.end()), B.end());
            int tmp = 0;
            for(int k = 0; k < n; k++, tmp++) {
                if(B[k] != tmp) break;
            }
            if(mex <= tmp) x = y, mex = tmp;
        }
        cout << x << "\n";
    }
    return 0;
}
