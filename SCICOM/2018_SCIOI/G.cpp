#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int N = 7;

ll seg[404040];
int ma[404040];

int f(int n) {
    if(n == 1) return 1;
    int res = 1;
    for(int i = 2; i*i <= n; i++) {
        int j = 1;
        while(n%i == 0) {
            n /= i;
            j++;
        }
        res *= j;
    }
    if(n != 1) res *= 2;
    return res;
}

void init(int i, int s, int e, vector<int>& A) {
    if(s+1 == e) {
        seg[i] = A[s];
        ma[i] = A[s];
    } else {
        init(i<<1, s, s+e>>1, A);
        init((i<<1)+1, s+e>>1, e, A);
        seg[i] = seg[i<<1]+seg[(i<<1)+1];
        ma[i] = max(ma[i<<1], ma[(i<<1)+1]);
    }
}

void update(int i, int s, int e, int l, int r) {
    if(e <= l || r <= s || ma[i] <= 2) return;
    if(s+1 == e) {
        seg[i] = f(seg[i]);
        ma[i] = seg[i];
    } else {
        update(i<<1, s, s+e>>1, l, r);
        update((i<<1)+1, s+e>>1, e, l, r);
        seg[i] = seg[i<<1]+seg[(i<<1)+1];
        ma[i] = max(ma[i<<1], ma[(i<<1)+1]);
    }
}

ll query(int i, int s, int e, int l, int r) {
    if(e <= l || r <= s) return 0LL;
    if(l <= s && e <= r) return seg[i];
    return query(i<<1, s, s+e>>1, l, r)+query((i<<1)+1, s+e>>1, e, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    init(1, 0, n, A);
    for(int i = 0; i < q; i++) {
        int t, s, e; cin >> t >> s >> e;
        if(--t) cout << query(1, 0, n, --s, e) << "\n";
        else update(1, 0, n, --s, e);
    }
    return 0;
}