#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string n;
    cin >> n;
    int tmp = 0;
    for(auto &i : n)
        tmp += i-'0';
    if(tmp%9 == 1) cout << 1;
    else cout << 0;
    return 0;
}