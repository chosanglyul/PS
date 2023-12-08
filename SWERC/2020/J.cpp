#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int R, D, C;

int num(int i, int c) {
    return (C+1)*i + c;
}

const int MAX_N = 1000 + 1;

int nse[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> R >> D >> C;
    vector<tuple<int, int, int>> edges;
    vector<int> outgoing(R, 0);
    for (int i=0; i<D; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({ a, b, c });
        outgoing[a] |= (1 << c);
    }
    for (int i=0; i<C; ++i) {
        if (outgoing[R-1] & (1 << i)) continue;
        edges.push_back({ R-1, R-1, i });
    }

    for (int i=0; i<(C+1)*R; ++i) nse[i][i] = 1;
    bool updated = true;
    while (updated) {
        updated = false;
        for (int i=0; i<edges.size(); ++i) {
            for (int j=0; j<edges.size(); ++j) {
                auto[a, b, c1] = edges[i];
                auto[p, q, c2] = edges[j];
                if (c1 == c2 && nse[num(b,c1)][num(p,c1)] == 1) {
                    for (int k=0; k<=C; ++k) {
                        if (!(outgoing[a] & (1 << k))) {
                            updated = updated | (nse[num(a,k)][num(q,k)] == 0);
                            nse[num(a,k)][num(q,k)] = 1;
//                            cout << c1 << ' ' << a << ' ' << b << ' ' << p << ' ' << q << ' ' << k << endl;
                        }
                    }
                }
            }
        }
//        cout << updated << endl;
    }
    /*
    for (int i=0; i<(C+1)*R; ++i) {
        for (int j=0; j<(C+1)*R; ++j) {
            cout << nse[i][j] << ' ';
        }
        cout << endl;
    }
    */

    const int INF = 0x3f3f3f3f;
    for (int i=0; i<(C+1)*R; ++i) {
        for (int j=0; j<(C+1)*R; ++j) {
            nse[i][j] = (nse[i][j] == 1 ? 0 : INF);
        }
    }

    for (auto[a, b, c]: edges) {
        for (int i=0; i<=C; ++i) {
            nse[num(a,c)][num(b,i)] = min(nse[num(a,c)][num(b,i)], 1);
        }
    }

    deque<int> dq;
    vector<int> dist((C+1)*R, INF);
    for (int i=0; i<=C; ++i) {
        dist[num(0,i)] = 0;
        dq.push_back(num(0,i));
    }
    while (!dq.empty()) {
        int here = dq.front();
        dq.pop_front();
//        cout << here << ' ' << dist[here] << endl;
        for (int i=0; i<(C+1)*R; ++i) {
            if (nse[here][i] == INF) continue;
            if (dist[i] > dist[here] + nse[here][i]) {
                dist[i] = dist[here] + nse[here][i];
                if (nse[here][i] == 1) {
                    dq.push_back(i);
                } else {
                    dq.push_front(i);
                }
            }
        }
    }

    int ans = INF;
    for (int i=0; i<=C; ++i) ans = min(ans, dist[num(R-1,i)]);
    cout << ans;

    return 0;
}