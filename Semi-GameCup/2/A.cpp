#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int k; cin >> k;
    vector<bool> A(k+1, false);
    for(int i = k; i > 0; i--) {
        for(int j = 1; j*j <= i; j++) {
            if(i%j == 0) {
                if(i+j <= k && A[i+j] == false) A[i] = true;
                if(i+i/j <= k && A[i+i/j] == false) A[i] = true;
            }
        }
    }
    if(A[1]) cout << "Kali\n";
    else cout << "Ringo\n";
    return 0;
}