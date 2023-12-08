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
    set<int> S; // values
    vector<pil> A; // idx, score
    vector<pii> cnt(1010101, {0, 0}); // cnt, idx, t
    int t = 0;
    while(q--) {
        int x, y; cin >> x >> y;
        if(x == 1) {
            int tmp = cnt[y].se;
            cnt[y].fi++;
            cnt[y].se ^= (int)A.size();
            A.push_back({y, 0LL});
            if(cnt[y].fi == 1) S.insert(y);
            else if(cnt[y].fi == 2) S.erase(y);
        } else if(x == 2) {
            int z = A[--y].fi;
            int tmp = cnt[z].se;
            cnt[z].fi--;
            cnt[z].se ^= y;
            if(cnt[z].fi == 1) S.insert(z);
            else if(cnt[z].fi == 0) S.erase(z);
        } else {
            t++;
            for(auto i : S) A[cnt[i].se].se++;
            if(S.size()) A[cnt[*prev(S.end())].se].se += y;
        }
    }
    for(auto i : A) cout << i.se << "\n";
    return 0;
}
