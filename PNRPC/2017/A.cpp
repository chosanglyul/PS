#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    int n = s.size();
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j <= n; j++) {
            bool can = true;
            for(int k = 0; k < j-i; k++)
                if(s[i+k] != s[j-1-k]) can = false;
            if(can && (j-i)%2 == 0) {
                cout << "Or not.\n";
                return 0;
            }
        }
    }
    cout << "Odd.\n";
    return 0;
}
