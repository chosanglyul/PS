#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> chk(n);
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        chk[i] = i%10 == 0 || i%10 == 3 || i%10 == 6;
        cnt += chk[i];
    }
    while(q--) {
        int x; cin >> x; --x;
        cnt += 1-2*chk[x];
        cout << cnt << "\n";
    }
    return 0;
}