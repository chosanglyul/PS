#include <bits/stdc++.h>
using namespace std;

vector<int> getPi(string &s) {
    vector<int> pi(s.size(), 0);
    for(int i = 1, j = 0; i < s.size(); i++) {
        while(j && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) pi[i] = ++j;
    }
    return pi;
}

vector<int> match(string &s, vector<int> &pi, string &t) {
    vector<int> ans;
    for(int i = 0, j = 0; i < s.size(); i++) {
        while(j && t[j] != s[i]) j = pi[j-1];
        if(s[i] == t[j]) ++j;
        if(j == t.size()) {
            ans.push_back(i);
            j = pi[j-1];
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    getline(cin, s);
    getline(cin, t);

    vector<int> pi = getPi(t);
    vector<int> ans = match(s, pi, t);
    cout << ans.size() << '\n';
    for(auto i : ans) cout << i-t.size()+2 << " ";
    cout << "\n";

    return 0;
}
