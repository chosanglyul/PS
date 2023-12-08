#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m, w; cin >> n >> m >> w;
        vector<piii> E;
        for(int i = 0; i < m; i++) {
            int x, y, z; cin >> x >> y >> z; --x, --y;
            E.push_back({z, {x, y}});
            E.push_back({z, {y, x}});
        }
        for(int i = 0; i < w; i++) {
            int x, y, z; cin >> x >> y >> z; --x, --y;
            E.push_back({-z, {x, y}});
        }

        vector<ll> D(n, 0LL);
        for(int i = 0; i < n; i++) {
            for(auto &[z, xy] : E) {
                if(D[xy.se] > z+D[xy.fi]) {
                    D[xy.se] = z+D[xy.fi];
                    if(i == n-1) {
                        cout << "YES\n";
                        goto L;
                    }
                }
            }
        }
        cout << "NO\n";
        L:;
    }
    return 0;
}