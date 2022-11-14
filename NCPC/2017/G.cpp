#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

class segtree {
    private:
    int n;
    vector<int> seg;
    void update(int i, int s, int e, int j, int x) {
        if(j >= e || j < s) return;
        if(s+1 == e) seg[i] += x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(l >= e || s >= r) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    segtree(int n) {
        this->n = n;
        seg = vector<int>(4*n, 0);
    }
    void update(pi x, int diff, vector<pi>& T) {
        int idx = lower_bound(T.begin(), T.end(), x) - T.begin();
        //cout << "update " << idx << " " << diff << "\n";
        update(1, 0, n, idx, diff);
    }
    int query(pi x, vector<pi>& T) {
        int idx = lower_bound(T.begin(), T.end(), x) - T.begin();
        //for(auto i : seg) cout << i << " ";
        //cout << "\n";
        //cout << "query " << idx << "\n";
        return query(1, 0, n, idx+1, n);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<pi> A(n, {0, 0}), T(1, {0, 0}), Q;
    while(m--) {
        int x, y; cin >> x >> y; --x;
        Q.push_back({x, y});
        A[x].fi++, A[x].se -= y;
        T.push_back(A[x]);
    }
    sort(T.begin(), T.end());
    T.erase(unique(T.begin(), T.end()), T.end());
    //for(auto i : T) cout << i.fi << " " << i.se << "  ";
    //cout << "\n";
    segtree S(T.size());
    for(auto &i : A) i = {0, 0};
    S.update({0, 0}, n, T);
    for(auto q : Q) {
        S.update(A[q.fi], -1, T);
        A[q.fi].fi++, A[q.fi].se -= q.se;
        S.update(A[q.fi], 1, T);
        cout << S.query(A[0], T) + 1 << "\n";
    }
    return 0;
}