#include <bits/stdc++.h>
using namespace std;

int solve(string &s) {
    int n = s.size();
    sort(s.begin(), s.end());
    int ma = 0;
    char mac = 'A';
    for(char c = 'A'; c <= 'Z'; c++) {
        int cnt = upper_bound(s.begin(), s.end(), c) - lower_bound(s.begin(), s.end(), c);
        if(ma < cnt) {
            mac = c;
            ma = cnt;
        }
    }
    fill(s.begin(), s.end(), mac);
    return n - ma;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<string> S(k*k);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c; cin >> c;
            S[(i%k)*k+(j%k)].push_back(c);
        }
    }
    int ans = 0;
    for(auto &i : S) ans += solve(i);
    cout << ans << "\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << S[(i%k)*k+(j%k)][0];
        }
        cout << "\n";
    }
    return 0;
}