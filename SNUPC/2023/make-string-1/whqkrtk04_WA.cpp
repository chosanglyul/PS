#include <bits/stdc++.h>
using namespace std;

string S, ans;
vector<int> T;

void solve(int s, int e) {
    int cnt = 0;
    while(s <= e && S[s] != S[e]) {
        ans += S[s];
        ans += 'N';
        s++, e--, cnt++;
    }
    if(s > e) return;
    vector<int> cut = {s};
    int tmp = 0;
    for(int i = s; i <= e; i++) {
        tmp += T[i];
        if(tmp == 0) cut.push_back(i);
    }
    // cout << cut.size() << "\n";
    // for(auto i : cut) cout << i << " ";
    // cout << "\n";
    for(int i = (int)cut.size()-2; i >= 0; i--)
        solve(cut[i], cut[i+1]);
    while(cnt--) ans += 'N';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    T.resize(n);
    cin >> S;
    for(int i = 0; i < n; i++) T[i] = (S[i] == 'S' ? 1 : -1);
    solve(0, n-1);
    cout << ans.size() << "\n";
    for(int i = 0; i < (int)ans.size(); i++) cout << ans[i];
    cout << "\n";
    return 0;
}
