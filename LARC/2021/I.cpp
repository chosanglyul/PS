#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int solve(int x, int y) {
    return ((y-x)%7+7)%7;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> M = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    string s; cin >> s;
    int idx;
    for(int i = 0; i < M.size(); i++) if(M[i] == s) idx = i;
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) {
        cin >> i;
        do {
            int tmp = solve(i, idx);
            switch(tmp) {
                case 1: i -= 30; break;
                case 2: i -= 30; break;
                case 3: i -= 32; break;
                case 4: i -= 31; break;
                default:
                    if(i >= 91) i %= 91;
                    else i -= 30;
            }
        } while(i > 0);
        i = -i;
    }
    cout << *min_element(A.begin(), A.end()) << '\n';
    return 0;
}