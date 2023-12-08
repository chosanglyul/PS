#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<int, ll> pil;
#define fi first
#define se second
const int INF = (int)1e9+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q; cin >> q;
    vector<int> S; // unique values
    vector<pil> A; // idx, score
    vector<piii> cnt(1010101, {0, {0, 0}}); // cnt, idx, t
    int t = 0, gma = 0;
    while(q--) {
        int x, y; cin >> x >> y;
        if(x == 1) {
            int tmp = cnt[y].se.fi;
            cnt[y].fi++;
            cnt[y].se.fi ^= (int)A.size();
            A.push_back({y, 0LL});
            if(cnt[y].fi == 1) {
                cnt[y].se.se = t;
                S.push_back(y);
                gma = max(gma, y);
            } else if(cnt[y].fi == 2) {
                A[tmp].se += t-cnt[y].se.se;
                if(gma == y) gma = INF;
            }
        } else if(x == 2) {
            int z = A[--y].fi;
            int tmp = cnt[z].se.fi;
            cnt[z].fi--;
            cnt[z].se.fi ^= y;
            if(cnt[z].fi == 1) {
                cnt[z].se.se = t;
                S.push_back(z);
                gma = max(gma, z);
            } else if(cnt[z].fi == 0) {
                A[tmp].se += t-cnt[z].se.se;
                if(gma == z) gma = INF;
            }
        } else {
            t++;
            int ma = 0;
            if(gma == INF) {
                int j = 0;
                for(int i = 0; i < S.size(); i++) {
                    if(cnt[S[i]].fi == 1) {
                        S[j++] = S[i];
                        ma = max(ma, S[i]);
                    }
                }
                gma = ma;
                S.resize(j);
            } else ma = gma;
            if(S.size() && ma) A[cnt[ma].se.fi].se += y;
        }
    }
    for(auto i : cnt) if(i.fi == 1) A[i.se.fi].se += t-i.se.se;
    for(auto i : A) cout << i.se << "\n";
    return 0;
}
