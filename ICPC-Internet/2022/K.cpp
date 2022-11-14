#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second
const int INF = (int)1e9+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t, m; cin >> n >> t >> m;
    int s, e; cin >> s >> e;
    vector<int> D(n, INF);
    D[s] = 0;
    for(int i = 0; i < t; i++) {
        vector<int> T(D);
        for(int j = 0; j < m; j++) {
            int s, e, w; cin >> s >> e >> w;
            T[e] = min(T[e], D[s]+w);
            T[s] = min(T[s], D[e]+w);
        }
        D = T;
    }
    cout << (D[e] == INF ? -1 : D[e]) << "\n";
    return 0;
}