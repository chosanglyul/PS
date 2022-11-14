#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    set<int> S;
    int n, m, k; cin >> n >> m >> k;
    vector<pii> A(k);
    for(auto &i : A) cin >> i.fi >> i.se;
    sort(A.begin(), A.end());
    for(auto i : A) {
        auto iter = S.upper_bound(i.se);
        if(iter != S.begin()) S.erase(--iter);
        S.insert(i.se);
    }
    //for(auto i : S) cout << i << " ";
    //cout << "\n";
    cout << S.size() << "\n";
    return 0;
}