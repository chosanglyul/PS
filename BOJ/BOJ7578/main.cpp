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

int seg[2020202];

void update(int i, int s, int e, int j) {
    if(s > j || e <= j) return;
    if(s+1 == e) seg[i]++;
    else {
        update(i<<1, s, s+e>>1, j);
        update((i<<1)+1, s+e>>1, e, j);
        seg[i] = seg[i<<1]+seg[(i<<1)+1];
    }
}

int query(int i, int s, int e, int l, int r) {
    if(s >= r || l >= e) return 0;
    if(l <= s && e <= r) return seg[i];
    return query(i<<1, s, s+e>>1, l, r)+query((i<<1)+1, s+e>>1, e, l, r);
}

int idx[1010101];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> A(n), B(n);
    for(auto &i : A) cin >> i;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        idx[x] = i;
    }
    for(int i = 0; i < n; i++) B[i] = idx[A[i]];
    ll cnt = 0;
    for(auto i : B) {
        cnt += query(1, 0, n, i+1, n);
        update(1, 0, n, i);
    }
    cout << cnt << endl;
    return 0;
}