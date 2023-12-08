#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    int ans = 0;
    for(int i = 0; i <= n+m; i++) {
        for(int x = 0; x <= n; x++)
            for(int y = 0; y <= m; y++)
                if(x+y == i) ans++;
    }
    cout << ans << endl;
    return 0;
}
