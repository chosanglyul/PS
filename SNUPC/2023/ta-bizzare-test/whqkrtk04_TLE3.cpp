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
    priority_queue<int> S; // TODO make pq
    vector<pii> cnt(1010101, {-1, -1});
    vector<vector<int>> U(1010101);
    int t = 0, n = 0;
    while(q--) {
        int x, y; cin >> x >> y;
        if(x == 1) {
            A.push_back({y, 0LL});
            int z = (U[y].size() ? *U[y].begin() : -1);
            U[y].push_back(n++);
            if(U[y].size() == 1) {
                cnt[y] = {*U[y].begin(), t};
                S.push(y);
            } else if(U[y].size() == 2) {
                A[z].se += t-cnt[y].se;
                cnt[y] = {-1, -1};
            }
        } else if(x == 2) {
            int z = A[--y].fi;
            U[z].erase(find(U[z].begin(), U[z].end(), y));
            if(U[z].size() == 0) {
                A[y].se += t-cnt[z].se;
                cnt[z] = {-1, -1};
            } else if(U[z].size() == 1) {
                cnt[z] = {*U[z].begin(), t};
                S.push(z);
            }
        } else {
            t++;
            while(S.size() && U[S.top()].size() != 1) S.pop();
            if(S.size()) A[*U[S.top()].begin()].se += y;
        }
    }
    for(auto i : cnt) if(i.se >= 0) A[i.fi].se += t-i.se;
    for(auto i : A) cout << i.se << "\n";
    return 0;
}
