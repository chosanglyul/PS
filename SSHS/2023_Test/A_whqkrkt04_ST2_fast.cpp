#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> chk(n);
    for(int i = 0; i < n; i++)
        chk[i] = i%10 == 0 || i%10 == 3 || i%10 == 6;
    for(int i = 0; i < q; i++) {
        int x; cin >> x; --x;
        chk[x] = 1-chk[x];
        int ans = 0;
        for(int j = 0; j < n; j++) ans += chk[j];
        cout << ans << "\n";
    }
    return 0;
}