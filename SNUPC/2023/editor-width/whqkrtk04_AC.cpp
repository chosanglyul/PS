#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int> idx = {0};
    for(int i = 1; i < n; i++)
        if(s[i-1] != s[i]) idx.push_back(i);
    idx.push_back(n);
    vector<pii> ran;
    for(int i = 1; i < idx.size(); i++)
        if(idx[i]-idx[i-1] >= k) ran.push_back({idx[i-1], idx[i]});
    for(int j = n; j > 0; j--) {
        int ans = 0;
        for(auto &i : ran) {
            pii tmp = {i.fi/j, i.se/j};
            if(tmp.fi == tmp.se) ans = max(ans, i.se-i.fi);
            else if(tmp.fi+1 == tmp.se) ans = max(ans, max(i.se%j, j-i.fi%j));
            else ans = max(ans, j);
            if(ans >= k) break;
        }
        if(ans < k) {
            cout << j << "\n";
            return 0;
        }
    }
    return 0;
}
