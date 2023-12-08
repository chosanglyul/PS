#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r = 0, t = 10;
    while(t--) {
        int x; cin >> x;
        if(x == 1) r += 90;
        if(x == 2) r += 180;
        if(x == 3) r += 270;
        r %= 360;
    }
    if(r == 0) cout << "N\n";
    else if(r == 90) cout << "E\n";
    else if(r == 180) cout << "S\n";
    else cout << "W\n";
    return 0;
}