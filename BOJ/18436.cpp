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
const int P = 1000000007;
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

class segtree {
    private:
    int n;
    vector<int> seg;
    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) seg[i] = (A[s]%2);
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(s >= r || l >= e) return 0;
        else if(l <= s && e <= r) return seg[i];
        else return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }
    void update(int i, int s, int e, int j, int x) {
        if(s > j || e <= j) return;
        else if(s+1 == e) seg[i] = (x%2);
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    public:
    segtree(vector<int>& A) {
        n = A.size();
        seg.resize(4*n);
        init(1, 0, n, A);
    }
    int query(int l, int r) { return query(1, 0, n, l, r); }
    void update(int j, int x) { update(1, 0, n, j, x); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    segtree s(A);
    int m; cin >> m;
    while(m--) {
        int t, x, y;
        cin >> t >> x >> y; --x;
        switch(t) {
        case 1:
        s.update(x, y);
        break;
        case 2:
        cout << y-x-s.query(x, y) << "\n";
        break;
        case 3:
        cout << s.query(x, y) << "\n";
        break;
        }
    }
    return 0;
}