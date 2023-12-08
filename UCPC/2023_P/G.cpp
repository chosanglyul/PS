#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    string s; cin >> s;
    vector<int> A(1, 0);
    for(int i = 0; i < n; i++)
        A.push_back(A.back()+(s[i] == 'S'));
    vector<int> B;
    for(int k = 1; k <= n; k++) {
        int t = k, cnt = 0;
        while(t <= n) {
            cnt++;
            int x = A[t];
            if(x >= k) break;
            t += k-x;
        }
        B.push_back(cnt);
    }
    for(auto &i : B) cout << i << " ";
    cout << "\n";
    return 0;
}
