#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<pi, pi> pii;
#define fi first
#define se second

ll seg[404040], ans[101010];
vector<int> A;

void init(int i, int s, int e) {
    if(s+1 == e) { seg[i] = A[s]; return; }
    init(i*2, s, (s+e)/2);
    init(i*2+1, (s+e)/2, e);
    seg[i] = seg[i*2]+seg[i*2+1];
}

void update(int i, int s, int e, int j, int x) {
    if(e <= j || s > j) return;
    if(s+1 == e) { seg[i] = x; return; }
    update(i*2, s, (s+e)/2, j, x);
    update(i*2+1, (s+e)/2, e, j, x);
    seg[i] = seg[i*2]+seg[i*2+1];
}

ll query(int i, int s, int e, int l, int r) {
    if(e <= l || s >= r) return 0;
    if(l <= s && e <= r) return seg[i];
    return query(i*2, s, (s+e)/2, l, r)+query(i*2+1, (s+e)/2, e, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n;
    A.resize(n);
    for(auto &i : A) cin >> i;
    cin >> q;
    vector<pi> Q;
    vector<pii> K;
    while(q--) {
        int x; cin >> x;
        if(x == 1) {
            int a, b; cin >> a >> b;
            Q.push_back({a, b});
        } else {
            int a, b, c; cin >> a >> b >> c;
            K.push_back({{a, K.size()}, {b, c}});
        }
    }
    sort(K.begin(), K.end());
    init(1, 0, n);
    int j = 0;
    for(auto &i : K) {
        for(; j < i.fi.fi; j++)
            update(1, 0, n, --Q[j].fi, Q[j].se);
        ans[i.fi.se] = query(1, 0, n, --i.se.fi, i.se.se);
    }
    for(int i = 0; i < K.size(); i++) cout << ans[i] << "\n";
    return 0;
}
