#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second
const ll LLINF = (ll)1e18+5;

int add_point(set<pii> &S, pii x) {
    int ans = 0;
    auto iter = S.lower_bound(x);
    if(iter != S.begin()) {
        auto jter = iter; jter--;
        ans += abs(jter->se - x.se);
        if(iter != S.end()) ans -= abs(jter->se - iter->se);
    }
    if(iter != S.end()) ans += abs(iter->se - x.se);
    S.insert(x);
    return ans;
}

int sub_point(set<pii> &S, pii x) {
    int ans = 0;
    S.erase(x);
    auto iter = S.lower_bound(x);
    if(iter != S.begin()) {
        auto jter = iter; jter--;
        ans -= abs(jter->se - x.se);
        if(iter != S.end()) ans += abs(jter->se - iter->se);
    }
    if(iter != S.end()) ans -= abs(iter->se - x.se);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    ll ans = 0LL;
    set<pii> S = {{A[0], 0}};
    for(int i = 1; i < k; i++) ans += add_point(S, {A[i], i});
    ll tmp = ans;
    for(int i = 0; i+k < n; i++) {
        tmp += sub_point(S, {A[i], i});
        tmp += add_point(S, {A[i+k], i+k});
        ans = min(tmp, ans);
    }
    cout << ans << "\n";
    return 0;
}