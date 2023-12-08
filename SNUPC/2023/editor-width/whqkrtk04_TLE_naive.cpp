#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int> A(n+1, 0);
    for(int j = n; j > 0; j--) {
        int ans = 0, tmp = 0;
        for(int i = 0; i < n; i++, tmp++) {
            if(i%j == 0 || (i && s[i-1] != s[i])) {
                ans = max(ans, tmp);
                tmp = 0;
            }
        }
        ans = max(ans, tmp);
        if(ans < k) {
            cout << j << "\n";
            return 0;
        }
    }
    return 0;
}
