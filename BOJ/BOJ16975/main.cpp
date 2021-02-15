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

ll seg[404040];

void update(int i, int s, int e, int j, int x) {
    if(j >= e || s > j) return;
    if(s+1 == e) {
        seg[i] += x;
    } else {
        update(i<<1, s, s+e>>1, j, x);
        update((i<<1)+1, s+e>>1, e, j, x);
        seg[i] = seg[i<<1]+seg[(i<<1)+1];
    }
}

ll query(int i, int s, int e, int l, int r) {
    if(l >= e || s >= r) return 0LL;
    if(l <= s && e <= r) return seg[i];
    return query(i<<1, s, s+e>>1, l, r) + query((i<<1)+1, s+e>>1, e, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    int m; cin >> m;
    while(m--) {
        int x; cin >> x;
        if(x == 1) {
            int y, z, k; cin >> y >> z >> k;
            update(1, 0, n, --y, k);
            if(z != n) update(1, 0, n, z, -k);
        } else {
            int y; cin >> y;
            cout << query(1, 0, n, 0, y)+A[y-1] << "\n";
        }
    }
    return 0;
}