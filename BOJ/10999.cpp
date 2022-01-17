#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9;
const ll LLINF = 1e18;

ll seg[4040404];
ll lazy[4040404];
vector<ll> A;

ll init(int i, int s, int e) {
    if(s+1 == e) return seg[i] = A[s];
    int mi = (s+e)/2;
    return seg[i] = init(i*2, s, mi) + init(i*2+1, mi, e);
}

void prop(int i, int s, int e) {
    if(s+1 != e) {
        int mi = (s+e)/2;
        seg[i*2] += (mi-s)*lazy[i];
        seg[i*2+1] += (e-mi)*lazy[i];
        lazy[i*2] += lazy[i];
        lazy[i*2+1] += lazy[i];
    }
    lazy[i] = 0;
}

ll query(int i, int s, int e, int l, int r) {
    if(s >= r || e <= l) return 0;
    if(l <= s && e <= r) return seg[i];
    prop(i, s, e);
    int mi = (s+e)/2;
    return query(i*2, s, mi, l, r) + query(i*2+1, mi, e, l, r);
}

ll update(int i, int s, int e, int l, int r, ll x) {
    if(s >= r || e <= l) return seg[i];
    if(l <= s && e <= r) {
        lazy[i] += x;
        return seg[i] += (e-s)*x;
    }
    prop(i, s, e);
    int mi = (s+e)/2;
    return seg[i] = update(i*2, s, mi, l, r, x) + update(i*2+1, mi, e, l, r, x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    A.resize(n);
    for(auto &i : A) cin >> i;
    init(1, 0, n);
    for(int i = 0; i < m+k; i++) {
        ll x, y, z;
        cin >> x;
        if(x == 1) {
            cin >> x >> y >> z;
            update(1, 0, n, --x, y, z);
        } else {
            cin >> x >> y;
            cout << query(1, 0, n, --x, y) << "\n";
        }
    }
    return 0;
}