#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int ans = (int)1e9+5;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        ans = min(ans, y/x);
    }
    cout << ans << "\n";
    return 0;
}