#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int l, r; cin >> l >> r;
        if(r >= 6) {
            cout << r << "\n";
        } else {
            string s = "";
            for(int i = l, j = (1<<l); i <= r; i++, j <<= 1)
                s += to_string(j);
            int x = stoi(s), y = 0;
            while(!(x&1)) x >>= 1, y++;
            cout << y << "\n";
        }
    }
    return 0;
}
