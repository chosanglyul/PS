#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    for(int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << endl;
        ll x; cin >> x;
        if(x == 0LL) {
            cout << "2 2" << endl;
            cout << "1 2" << endl;
        } else if(x > 100LL) {
            cout << "1 1" << endl;
            cout << "1" << endl;
        } else {
            cout << x+1 << " " << 2 << endl;
            cout << "1 ";
            for(int i = 0; i < x-1; i++) cout << "0 ";
            cout << "1" << endl;
        }
    }
    return 0;
}
