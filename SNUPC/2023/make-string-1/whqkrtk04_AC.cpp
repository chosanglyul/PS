#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    string s; cin >> s;
    vector<char> st, ans;
    for(int i = n-1; i >= 0; i--) {
        if(st.empty() || st.back() != s[i]) {
            if(s[i] == 'U') st.push_back('S');
            else st.push_back('U');
            ans.push_back(st.back());
            ans.push_back('N');
        } else {
            st.pop_back();
            ans.push_back('N');
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < (int)ans.size(); i++)
        cout << ans[i];
    cout << "\n";
    return 0;
}
