#include <bits/stdc++.h>
using namespace std;

void nope() {
    cout << "NOPE\n";
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    for(auto &i : A) {
        cin >> i;
        if(i > k || i <= 0) nope();
    }
    for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n-1; j++)
            if(A[i] == A[j] && A[i+1] == A[j+1]) nope();
    return 0;
}