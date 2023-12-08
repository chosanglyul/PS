#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<string> S(n);
    vector<bool> C(26, false);
    for(auto &i : S) {
        cin >> i;
        C[i[0]-'A'] = true;
    }
    for(auto &i : S) {
        bool can = true;
        for(auto j : i) {
            if(!C[j-'A']) can = false;
        }
        if(can) {
            cout << "Y\n";
            return 0;
        }
    }
    cout << "N\n";
    return 0;
}