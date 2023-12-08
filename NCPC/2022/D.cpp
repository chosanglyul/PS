#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll r; cin >> r;
    ll x = 0LL, y = r+1LL;
    ll ax = x, ay = y;
    while(x <= r) {
        while(x*x+y*y > r*r) y--;
        y++;
        if(ax*ax+ay*ay > x*x+y*y) ax = x, ay = y;
        x++;
    }
    cout << ax << " " << ay << "\n";
    return 0;
}