#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;
    string ans = s;
    for (int i=0; i<n; ++i) {
        if (s[i] == '1') {
            if (i+1 < n) ans[i+1] = '1';
            if (i+2 < n) ans[i+2] = '1';
        }
    }
    cout << count(ans.begin(), ans.end(), '1');

    return 0;
}