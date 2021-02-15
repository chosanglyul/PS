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

int seg[404040];

void init(int i, int s, int e, vector<int>& A) {
    if(s+1 == e) seg[i] = A[s];
    else {
        init(i<<1, s, s+e>>1, A);
        init(i<<1|1, s+e>>1, e, A);
        seg[i] = min(seg[i<<1], seg[i<<1|1]);
    }
}

int query(int i, int s, int e, int l, int r) {
    if(e <= l || r <= s) return INF;
    if(l <= s && e <= r) return seg[i];
    return min(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s; cin >> s;
    int m; cin >> m;
    vector<int> A(1, 0);
    for(int i = 0, x = 0; i < s.size(); i++) {
        if(s[i] == '(') x++;
        else x--;
        A.push_back(x);
    }
    init(1, 0, A.size(), A);
    int cnt = 0;
    while(m--) {
        int x, y; cin >> x >> y;
        if(A[--x] != A[y]) continue;
        if(A[x] <= query(1, 0, A.size(), x, y)) {
            //cout << A[x] << " " << A[y] << " " << x+1 << " " << y << "\n";
            cnt++;
        }
    }
    cout << cnt << "\n";
    return 0;
}