#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> solve(ll x) {
    if(x == 1LL) return {1};
    if(x == 2LL) return {1, 1};
    vector<int> A = solve((x-1LL)/2), B;
    int k = *max_element(A.begin(), A.end());
    bool maxfind = false;
    for(int i = 0; i < A.size(); i++) {
        B.push_back(A[i]);
        if(A[i] == k && !maxfind) {
            maxfind = true;
            B.push_back(k+1);
            if(x%2 == 0LL) B.push_back(k+1);
        }
    }
    B.push_back(k+1);
    B.push_back(k+1);
    return B;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    for(int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << endl;
        ll x; cin >> x;
        if(x == 0LL) {
            cout << "2 2" << endl;
            cout << "1 2" << endl;
        } else {
            vector<int> tmp = solve(x);
            int N = *max_element(tmp.begin(), tmp.end());
            vector<int> ans = {tmp[0]};
            for(int i = 1; i < tmp.size(); i++) ans.push_back(tmp[i]-tmp[i-1]);
            ans.push_back(N+1-tmp.back());
            cout << ans.size() << " " << N+1 << endl;
            for(auto i : ans) cout << i << " ";
            cout << endl;
        }
    }
    return 0;
}
