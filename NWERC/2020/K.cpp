#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s, t;
    getline(cin, s);
    getline(cin, t);
    int i = 0, j = 0;
    vector<char> A;
    while(i < s.size() && j < t.size()) {
        int x = i, y = j;
        while(x < s.size() && s[x] == s[i]) x++;
        while(y < t.size() && t[y] == t[j]) y++;
        if(y-j != x-i) A.push_back(s[i]);
        i = x, j = y;
    }
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    for(auto i : A) cout << i;
    cout << "\n";
    return 0;
}