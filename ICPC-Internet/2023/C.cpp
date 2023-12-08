#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);

    int ph = 0, pg = 0;
    for (int i=0; i<s.size(); ++i) {
        if (s[i] == 'H' || s[i] == 'A' || s[i] == 'P' || s[i] == 'Y') ph++;
        if (s[i] == 'S' || s[i] == 'A' || s[i] == 'D') pg++;
    }
    if (ph == 0 && pg == 0) {
        cout << "50.00";
    } else {
        double ans = 100.0 * ph / (ph+pg);
        cout << fixed << setprecision(2) << ans;
    }

    return 0;
}