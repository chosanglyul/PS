#include "fish.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll LLINF = (ll)1e18+5;
#define fi first
#define se second

typedef struct prefix_sum {
    vector<vector<pll>> B;
    ll operator()(int x, int s, int e) {
        assert(s <= e);
        return this->operator()(x, e)-this->operator()(x, s);
    }
    ll operator()(int x, int y) {
        if(x < 0 || x >= (int)B.size()) return 0LL;
        auto iter = lower_bound(B[x].begin(), B[x].end(), pll(y, 0LL));
        return (iter == B[x].begin() ? 0LL : (--iter)->se);
    }
    prefix_sum(vector<vector<pii>> &A) {
        for(auto &i : A) {
            ll su = 0LL;
            B.push_back(vector<pll>());
            for(auto &j : i) {
                su += j.se;
                B.back().push_back({j.fi, su});
            }
        }
    }
} prefix_sum;

ll max_weights(int N, int M, vector<int> X, vector<int> Y, vector<int> W) {
    vector<vector<pii>> brd(N);
    for(int i = 0; i < M; i++) brd[X[i]].push_back({Y[i], W[i]});
    for(int i = 0; i < N; i++) {
        brd[i].push_back({N, 0});
        sort(brd[i].begin(), brd[i].end());
    }
    prefix_sum pre(brd);

    vector<vector<pll>> down(N), dp(N);
    down[0].resize(brd[0].size()); dp[0].resize(brd[0].size());
    for(int j = 0; j < (int)brd[0].size(); j++) {
        down[0][j] = dp[0][j] = pll(brd[0][j].fi, pre(1, brd[0][j].fi));
    }
    down[1].resize(brd[1].size()); dp[1].resize(brd[1].size());
    for(int j = 0; j < (int)brd[1].size(); j++) {
        down[1][j] = dp[1][j] = pll(brd[1][j].fi, pre(0, brd[1][j].fi)+pre(2, brd[1][j].fi));
        dp[1][j].se = max(dp[1][j].se, pre(1, brd[1][j].fi, N)+pre(2, brd[1][j].fi));
    }
    for(int i = 2; i < N; i++) {
        vector<pll> A(down[i-1]), B(dp[i-2]), C(dp[i-2]), D(dp[i-1]);
        for(auto &j : A) j.se -= pre(i, j.fi)+pre(i-1, j.fi);
        for(auto &j : B) j.se -= pre(i-1, j.fi);
        for(int j = 1; j < (int)A.size(); j++) A[j].se = max(A[j].se, A[j-1].se);
        for(int j = 1; j < (int)B.size(); j++) B[j].se = max(B[j].se, B[j-1].se);
        for(int j = (int)C.size()-2; j >= 0; j--) C[j].se = max(C[j].se, C[j+1].se);
        for(int j = (int)D.size()-2; j >= 0; j--) D[j].se = max(D[j].se, D[j+1].se);
        for(auto &j : brd[i]) {
            pll h = {j.fi, LLINF};
            ll downtmp = 0LL, dptmp = 0LL;

            auto itera = upper_bound(A.begin(), A.end(), h);
            if(itera != A.begin()) downtmp = max(downtmp, (--itera)->se+pre(i-1, j.fi)+pre(i+1, j.fi));
            auto iterb = upper_bound(B.begin(), B.end(), h);
            if(iterb != B.begin()) downtmp = max(downtmp, (--iterb)->se+pre(i-1, j.fi)+pre(i+1, j.fi));

            auto iterc = upper_bound(C.begin(), C.end(), h);
            if(iterc != C.end()) downtmp = max(downtmp, iterc->se+pre(i+1, j.fi));
            auto iterd = upper_bound(D.begin(), D.end(), h);
            if(iterd != D.end()) dptmp = max(dptmp, iterd->se-pre(i, j.fi)+pre(i+1, j.fi));

            dptmp = max(dptmp, downtmp);
            down[i].push_back({h.fi, downtmp});
            dp[i].push_back({h.fi, dptmp});
        }
    }

    ll ans = 0LL;
    for(auto &j : dp.back()) ans = max(ans, j.se);
    return ans;
}
