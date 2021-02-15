#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1e9+7;
const ll LLINF = 1e18+1;

vector<pl> A[101010];
int n, m, cnt, k, s;

void solve() {
    multiset<pl> Q;
    Q.insert({0, --s});
    while(Q.size()) {
        auto b = Q.begin();
        pl tmp = *b; Q.erase(b);
        //cout << tmp.fi << " " << tmp.se << endl;
        if(++cnt == k) {
            cout << tmp.fi << "\n";
            return;
        }
        for(auto &i : A[tmp.se]) {
            if(Q.size() == k) {
                auto e = Q.end();
                pl ed = *(--e);
                if(ed.fi > i.se+tmp.fi) {
                    Q.erase(e);
                    Q.insert({i.se+tmp.fi, i.fi});
                }
            } else Q.insert({i.se+tmp.fi, i.fi});
        }
    }
    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k >> s;
    for(int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        A[--u].push_back({--v, t});
    }
    solve();
    return 0;
}