#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& A) {
    if(A[n] > -1) return A[n];
    if(n == 1) return A[n] = 0;
    A[n] = solve(n-1, A)+1;
    if(n%2 == 0) A[n] = min(A[n], solve(n/2, A)+1);
    if(n%3 == 0) A[n] = min(A[n], solve(n/3, A)+1);
    return A[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n+1, -1);
    cout << solve(n, A) << "\n";
    return 0;
}