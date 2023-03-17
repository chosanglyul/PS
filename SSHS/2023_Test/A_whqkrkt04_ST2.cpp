#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> Q(q);
    for(int i = 0; i < q; i++) {
        cin >> Q[i]; --Q[i];
        vector<int> chk(n);
        for(int j = 0; j < n; j++)
            chk[j] = j%10 == 0 || j%10 == 3 || j%10 == 6;
        for(int j = 0; j <= i; j++)
            chk[Q[j]] = 1-chk[Q[j]];
        int ans = 0;
        for(int j = 0; j < n; j++)
            ans += chk[j];
        cout << ans << "\n";
    }
    return 0;
}