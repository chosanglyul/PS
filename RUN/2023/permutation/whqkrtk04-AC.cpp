#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n);
        for(auto &i : A) { cin >> i; i--; }
        vector<bool> chk(n, false);
        int cnt = 0;
        vector<int> B;
        for(int i = 0; i+1 < n; i++) {
            if(A[i] <= i) cnt++;
            else chk[A[i]] = true;
            cnt += (chk[i] == true);
            if(cnt == i+1) B.push_back(cnt);
        }
        cout << B.size() << "\n";
        for(auto i : B) cout << i << " ";
        cout << "\n";
    }
    return 0;
}
