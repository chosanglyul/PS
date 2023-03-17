#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> chk(n);
    int cnt = (n/10)*3;
    if(n%10 > 0) cnt++;
    if(n%10 > 3) cnt++;
    if(n%10 > 6) cnt++;
    while(q--) cout << --cnt << "\n";
    return 0;
}