#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll tmp = 1LL, a = 1664525LL, b = 1013904223LL, p = 1LL<<32;
    int ans = 0;
    for(int i = 0; i < 29*5; i++) {
        tmp = (tmp*a+b)%p;
        ll tt = tmp;
        while(tt) {
            ans += tt%10;
            tt /= 10;
        }
    }
    cout << ans << "\n";
    return 0;
}