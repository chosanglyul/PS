#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second
const int INF = (int)1e9+5;

const int MAX_C = 1e5 + 1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> points(MAX_C);
    for (int i=0; i<n; ++i) {
        int x, y;
        cin >> x >> y;
        points[x].push_back(y);
    }
    for (int i=0; i<=MAX_C; ++i) sort(points[i].begin(), points[i].end());

    int sqrt = sqrtl(n);
    vector<int> under_rt, over_rt;
    for (int i=0; i<=MAX_C; ++i) {
        if (points[i].size() >= 2) {
            if (points[i].size() < sqrt) {
                under_rt.push_back(i);
            } else {
                over_rt.push_back(i);
            }
        }
    }

    ll ans = 0;
    // under-root
    map<pii, int> mp;
    for (int x: under_rt) {
        for (int i=0; i<points[x].size(); ++i) {
            for (int j=i+1; j<points[x].size(); ++j) {
                if (mp.find({points[x][i], points[x][j]}) != mp.end()) {
                    ans += mp[{points[x][i], points[x][j]}];
                }
            }
        }
        for (int i=0; i<points[x].size(); ++i) {
            for (int j=i+1; j<points[x].size(); ++j) {
                if (mp.find({points[x][i], points[x][j]}) != mp.end()) {
                    mp[{points[x][i], points[x][j]}]++;
                } else {
                    mp[{points[x][i], points[x][j]}] = 1;
                }
            }
        }
    }
    // cout << ans << endl;

    // under-over cross
    for (int x1: under_rt) {
        for (int x2: over_rt) {
            int tmp = 0;
            for (int y: points[x1]) {
                auto it = lower_bound(points[x2].begin(), points[x2].end(), y);
                if (it != points[x2].end() && *it == y) tmp++;
            }
            ans += tmp * (tmp-1) / 2;
        }
    }
    // cout << ans << endl;

    // cout << ans << ' ' << sqrt << endl;
    // over-root
    for (int i=0; i<over_rt.size(); ++i) {
        for (int j=i+1; j<over_rt.size(); ++j) {
            int x1 = over_rt[i];
            int x2 = over_rt[j];
            int p1 = 0, p2 = 0;
            int tmp = 0;
            // cout << "enter: " << x1 << ' ' << x2 << endl;
            while (p1 < points[x1].size() && p2 < points[x2].size()) {
                while (p1 < points[x1].size() && points[x1][p1] < points[x2][p2]) p1++;
                // cout << p1 << ' ' << p2 << endl;
                if (p1 < points[x1].size() && points[x1][p1] == points[x2][p2]) tmp++;
                p2++;
            }
            // cout << tmp << endl;
            ans += tmp * (tmp-1) / 2;
        }
    }

    cout << ans;
    return 0;
}