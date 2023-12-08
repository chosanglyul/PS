#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    sort(A.begin(), A.end());
    int idx = (n-1)/2;
    for(int i = 0; 0 <= idx && idx < n; i++) {
        if(i%2 == 0) idx -= i;
        else idx += i;
        if(0 <= idx && idx < n) cout << A[idx] << " ";
    }
    cout << "\n";
    return 0;
}