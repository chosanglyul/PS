#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<vector<int>> A(10);
        for(int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            A[--y].push_back(x);
        }
        bool can = true;
        for(auto &i : A) {
            if(i.empty()) can = false;
            sort(i.begin(), i.end());
        }
        if(can) {
            int ans = 0;
            for(auto &i : A) ans += i.back();
            cout << ans << "\n";
        } else {
            cout << "MOREPROBLEMS\n";
        }
    }
    return 0;
}