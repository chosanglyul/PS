#include <bits/stdc++.h>
using namespace std;

string solve(int idx, string& s) {
    string ret = {s[idx]};
    if(s[idx] == 'x') {
        vector<string> A(4);
        int tmp = 1;
        for(auto &i : A) {
            i = solve(idx+tmp, s);
            tmp += i.size();
        }
        swap(A[0], A[2]); swap(A[1], A[3]);
        for(auto &i : A) ret += i;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        cout << solve(0, s) << "\n";
    }
    return 0;
}