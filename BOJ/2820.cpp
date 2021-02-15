#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int P = 1e9+7;

int seg[4040404], lazy[4040404], in[505050], out[505050], cnt;
vector<int> A[505050];
bool chk[505050];

void dfs(int i) {
    if(chk[i]) return;
    in[i] = cnt++;
    chk[i] = true;
    for(auto j : A[i]) dfs(j);
    out[i] = cnt++;
}

void init(int i, int s, int e, vector<int>& A) {
    if(s+1 == e) seg[i] = A[s];
    else {
        init(i<<1, s, s+e>>1, A);
        init((i<<1)+1, s+e>>1, e, A);
        seg[i] = max(seg[i<<1], seg[(i<<1)+1]);
    }
}

void prop(int i, int s, int e) {
    if(s+1 != e && lazy[i]) {
        lazy[i<<1] += lazy[i];
        lazy[(i<<1)+1] += lazy[i];
        seg[i<<1] += lazy[i];
        seg[(i<<1)+1] += lazy[i];
    }
    lazy[i] = 0;
}

void update(int i, int s, int e, int l, int r, int x) {
    if(l >= e || s >= r) return;
    if(l <= s && e <= r) {
        lazy[i] += x;
        seg[i] += x;
    } else {
        prop(i, s, e);
        update(i<<1, s, s+e>>1, l, r, x);
        update((i<<1)+1, s+e>>1, e, l, r, x);
        seg[i] = max(seg[i<<1], seg[(i<<1)+1]);
    }
}

int query(int i, int s, int e, int l, int r) {
    if(l >= e || s >= r) return 0;
    if(l <= s && e <= r) return seg[i];
    prop(i, s, e);
    return max(query(i<<1, s, s+e>>1, l, r), query((i<<1)+1, s+e>>1, e, l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> B(n), C(2*n);
    cin >> B[0];
    for(int i = 1; i < n; i++) {
        int x; cin >> B[i] >> x;
        A[--x].push_back(i);
    }
    dfs(0);
    for(int i = 0; i < n; i++) C[in[i]] = B[i];
    for(int i = 0; i < n; i++) C[out[i]] = B[i];
    init(1, 0, 2*n, C);
    for(int i = 0; i < m; i++) {
        char c; cin >> c;
        if(c == 'p') {
            int x, y; cin >> x >> y; --x;
            update(1, 0, 2*n, in[x]+1, out[x], y);
        } else {
            int x; cin >> x; --x;
            cout << query(1, 0, 2*n, in[x], in[x]+1) << "\n";
        }
    }
    return 0;
}