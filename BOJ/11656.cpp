#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    vector<string> SA;
    for(int i = 0; i < s.size(); i++)
        SA.push_back(string(s.begin()+i, s.end()));
    sort(SA.begin(), SA.end());
    for(auto &i : SA) cout << i << "\n";
    return 0;
}