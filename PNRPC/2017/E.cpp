#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x; double v; cin >> n >> x >> v;
    double su = 0.0;
    for(int i = 0; i < n; i++) {
        int l, r; double u; cin >> l >> r >> u;
        su += (r-l)*u;
    }
    double tmp = su*su/(v*v*(ll)x*(ll)x-su*su);
    if(tmp < 0) {
        cout << "Too hard\n";
        return 0;
    }
    tmp = sqrt(1.0+tmp);
    if(tmp > 2) {
        cout << "Too hard\n";
        return 0;
    }
    cout << fixed << setprecision(3) << tmp*x/v << "\n";
    return 0;
}
