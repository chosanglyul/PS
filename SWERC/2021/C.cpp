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

    int n; ll v; cin >> n >> v;
    vector<ll> t(n), a(n);
    for (auto &x: t) cin >> x;
    for (auto &x: a) cin >> x;

    vector<int> dp(n, 0);
    vector<set<pll>> s;
    s.push_back(set<pll>());
    s[0].insert({ 0, 0 });
    for (int i=0; i<n; ++i) {
        ll y = -v*t[i]+a[i], x = v*t[i]+a[i];
        int low = -1, high = s.size();
        while (low+1 < high) {
            int mid = low+high>>1;
            auto it = s[mid].upper_bound({ x, LLINF });
            if (it != s[mid].begin() && prev(it)->second >= y) low = mid;
            else high = mid;
        }
        if(low >= 0) {
            dp[i] = low+1;
            if (dp[i] == s.size()) s.push_back(set<pll>());
            s[dp[i]].insert({ x, y });
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";

    return 0;
}