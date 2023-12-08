#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<int, ll> pil;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q; cin >> q;
    vector<pil> A;
    set<int> S;
    vector<pii> cnt(1010101, {-1, -1});
    vector<set<int>> U(1010101);
    int t = 0, n = 0;
    while(q--) {
        int x, y; cin >> x >> y;
        if(x == 1) {
            A.push_back({y, 0LL});
            int z = (U[y].size() ? *U[y].begin() : -1);
            U[y].insert(n++);
            if(U[y].size() == 1) {
                cnt[y] = {*U[y].begin(), t};
                S.insert(y);
            } else if(U[y].size() == 2) {
                A[z].se += t-cnt[y].se;
                cnt[y] = {-1, -1};
                S.erase(y);
            }
        } else if(x == 2) {
            int z = A[--y].fi;
            U[z].erase(y);
            if(U[z].size() == 0) {
                A[y].se += t-cnt[z].se;
                cnt[z] = {-1, -1};
                S.erase(z);
            } else if(U[z].size() == 1) {
                cnt[z] = {*U[z].begin(), t};
                S.insert(z);
            }
        } else {
            t++;
            if(S.size()) A[*U[*prev(S.end())].begin()].se += y;
        }
    }
    for(auto i : cnt) if(i.se >= 0) A[i.fi].se += t-i.se;
    for(auto i : A) cout << i.se << "\n";
    return 0;
}
