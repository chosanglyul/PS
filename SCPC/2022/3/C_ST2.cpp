#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
        } else if(x > 100000LL) {
            cout << "1 1" << endl;
            cout << "1" << endl;
        } else {
            const int N = 20;
            vector<int> ans;
            for(int i = 0; i+1 < N; i++) ans.push_back(1);
            ans.push_back(-N+1);
            for(int i = 0; i+1 < N; i++) {
                if(x&(1LL<<i)) {
                    ans.push_back(N-i);
                    ans.push_back(-1);
                } else ans.push_back(N-i-1);
                for(int j = N-1; j > i+1; j--) ans.push_back(-1);
            }
            ans.push_back(2);
            cout << ans.size() << " " << N+1 << endl;
            for(auto i : ans) cout << i << " ";
            cout << endl;
        }
    }
    return 0;
}
