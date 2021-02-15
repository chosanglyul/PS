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

pi seg[808080];

pi merge(pi a, pi b) {
    pi res;
    res.fi = max(a.fi, b.fi);
    res.se = min(a.se, b.se);
    return res;
}

void init(int i, int s, int e, vector<int>& A) {
    if(s+1 == e) seg[i].fi = seg[i].se = A[s];
    else {
        init(i<<1, s, s+e>>1, A);
        init((i<<1)+1, s+e>>1, e, A);
        seg[i] = merge(seg[i<<1], seg[(i<<1)+1]);
    }
}

void update(int i, int s, int e, int j, int x) {
    if(s > j || e <= j) return;
    if(s+1 == e) seg[i].fi = seg[i].se = x;
    else {
        update(i<<1, s, s+e>>1, j, x);
        update((i<<1)+1, s+e>>1, e, j, x);
        seg[i] = merge(seg[i<<1], seg[(i<<1)+1]);
    }
}

pi query(int i, int s, int e, int l, int r) {
    if(l >= e || s >= r) return {-INF, INF};
    if(l <= s && e <= r) return seg[i];
    return merge(query(i<<1, s, s+e>>1, l, r), query((i<<1)+1, s+e>>1, e, l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> A(n), B(n);
    for(auto &i : B) cin >> i;
    for(int i = 0; i < n; i++) A[--B[i]] = i;
    init(1, 0, n, A);
    for(int i = 0; i < m; i++) {
        int x, y, z; cin >> x >> y >> z;
        if(--x) {
            pi tmp = query(1, 0, n, y-1, z);
            /*for(auto i : A) cout << i << " ";
            cout << "\n";
            for(auto i : B) cout << i << " ";
            cout << "\n" << tmp.fi << " " << tmp.se << "\n";*/
            if(tmp.fi-tmp.se == z-y) cout << "YES\n";
            else cout << "NO\n";
        } else {
            --y, --z;
            update(1, 0, n, B[y], A[B[z]]);
            update(1, 0, n, B[z], A[B[y]]);
            swap(A[B[y]], A[B[z]]);
            swap(B[y], B[z]);
        }
    }
    return 0;
}