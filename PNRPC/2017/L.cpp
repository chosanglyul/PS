#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, p, x; cin >> k >> p >> x;
    double ans = 1e18;
    int tmp = (int)sqrt((double)k*p/x);
    for(int i = max(tmp-10, 1); i <= tmp+10; i++) {
        double d = (double)k/i;
        ans = min(ans, d*p+x*i);
    }
    cout << fixed << setprecision(3) << ans << "\n";
    return 0;
}