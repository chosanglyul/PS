#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    string s, t; cin >> s;
    reverse(s.begin(), s.end());
    vector<char> ans;
    for(int i = 0, idx = 0; i < n; i++, idx++) {
        if(idx >= t.size() || s[i] != t[idx]) {
            if(s[i] == 'U') t.insert(idx, "US", 2), ans.push_back('S');
            else t.insert(idx, "SU", 2), ans.push_back('U');
        }
        ans.push_back('N');
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < (int)ans.size(); i++) cout << ans[i];
    cout << "\n";
    return 0;
}
