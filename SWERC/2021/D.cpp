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
    int n, m; cin >> n >> m;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<int> B(m);
    for(auto &i : B) cin >> i;
    sort(B.begin(), B.end());
    vector<pii> C, D;
    for(int i = 0, j = 0; i < n; i++, j += 100) {
        int tmp = INF;
        auto iter = upper_bound(B.begin(), B.end(), j);
        if(iter != B.begin()) tmp = min(tmp, j-(*(--iter)));
        auto jter = lower_bound(B.begin(), B.end(), j);
        if(jter != B.end()) tmp = min(tmp, (*jter)-j);
        C.push_back({j-tmp, A[i]});
        D.push_back({j+tmp, A[i]});
        // cout << i << " " << A[i] << " " << j-tmp << " " << j+tmp << endl;
    }
    sort(C.begin(), C.end());
    sort(D.begin(), D.end());
    ll ans = 0LL, tmp = 0LL;
    for(int i = 0, j = 0, k = C.front().fi; k <= D.back().fi; k++) {
        while(j < D.size() && D[j].fi == k) tmp -= D[j++].se;
        ans = max(ans, tmp);
        while(i < C.size() && C[i].fi == k) tmp += C[i++].se;
        ans = max(ans, tmp);
    }
    cout << ans << "\n";
    return 0;
}
