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
    vector<int> S; // unique values
    vector<pil> A; // idx, score
    vector<piii> cnt(1010101, {0, {0, 0}}); // cnt, idx, t
    int t = 0;
    while(q--) {
        int x, y; cin >> x >> y;
        if(x == 1) {
            int tmp = cnt[y].se.fi;
            cnt[y].fi++;
            cnt[y].se.fi ^= (int)A.size();
            A.push_back({y, 0LL});
            if(cnt[y].fi == 1) {
                cnt[y].se.se = t;
                S.insert(lower_bound(S.begin(), S.end(), y), y);
            } else if(cnt[y].fi == 2) {
                A[tmp].se += t-cnt[y].se.se;
                S.erase(find(S.begin(), S.end(), y));
            }
        } else if(x == 2) {
            int z = A[--y].fi;
            int tmp = cnt[z].se.fi;
            cnt[z].fi--;
            cnt[z].se.fi ^= y;
            if(cnt[z].fi == 1) {
                cnt[z].se.se = t;
                S.insert(lower_bound(S.begin(), S.end(), z), z);
            } else if(cnt[z].fi == 0) {
                A[tmp].se += t-cnt[z].se.se;
                S.erase(find(S.begin(), S.end(), z));
            }
        } else {
            t++;
            if(S.size()) A[cnt[*prev(S.end())].se.fi].se += y;
        }
    }
    for(auto i : cnt) if(i.fi == 1) A[i.se.fi].se += t-i.se.se;
    for(auto i : A) cout << i.se << "\n";
    return 0;
}
