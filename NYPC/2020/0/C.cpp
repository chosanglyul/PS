#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int l = 1, r = 1001;
    while(1) {
        int mi = l+r>>1;
        cout << mi << endl;
        string s; cin >> s;
        if(s == "UP") l = mi;
        else if(s == "DOWN") r = mi;
        else return 0;
    }
}