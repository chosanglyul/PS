#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    cout << fixed << setprecision(15);
    for(int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << endl;
        double ma = 0, mi = 0;
        int n; cin >> n;
        vector<double> A(n);
        for(auto &i : A) cin >> i;
        sort(A.begin(), A.end());
        double ans = 0;
        int i = 0, j = 0, cnt = 0;
        while(i < n) {
            while(j < n && A[i] == A[j]) j++;
            int tmp = j-i;
            double a = (double)cnt/n-A[i], b = (double)(cnt+tmp)/n-A[i];
            ans = max(ans, abs(a-b));
            if(i) {
                ans = max(ans, max(abs(a-mi), abs(a-ma)));
                ans = max(ans, max(abs(b-mi), abs(b-ma)));
            }
            mi = min(mi, min(a, b));
            ma = max(ma, max(a, b));
            // cout << a << " " << b << " " << mi << " " << ma << " " << ans << "\n";
            i = j, cnt += tmp;
        }
        ans = max(ans, max(abs(ma), abs(mi)));
        cout << ans << endl;
    }
    return 0;
}
