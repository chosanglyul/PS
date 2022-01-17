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
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

vector<pi> seg, lazy;

pi merge(pi a, pi b) {
    if(a.fi > b.fi) return b;
    else return a;
}

void prop(int i, int s, int e) {
    if(s+1 != e) {
        seg[i*2] = merge(seg[i*2], lazy[i]);
        seg[i*2+1] = merge(seg[i*2+1], lazy[i]);
        lazy[i*2] = merge(lazy[i*2], lazy[i]);
        lazy[i*2+1] = merge(lazy[i*2+1], lazy[i]);
    }
    lazy[i] = {INF, -1};
}

pi query(int i, int s, int e, int l, int r) {
    if(s >= r || e <= l) return {INF, -1};
    if(l <= s && e <= r) return seg[i];
    prop(i, s, e);
    return merge(query(i*2, s, s+e>>1, l, r), query(i*2+1, s+e>>1, e, l, r));
}

void update(int i, int s, int e, int l, int r, pi x) {
    if(s >= r || e <= l) {
        return;
    } else if(l <= s && e <= r) {
        lazy[i] = merge(lazy[i], x);
        seg[i] = merge(seg[i], x);
    } else {
        prop(i, s, e);
        update(i*2, s, s+e>>1, l, r, x);
        update(i*2+1, s+e>>1, e, l, r, x);
        seg[i] = merge(seg[i*2], seg[i*2+1]);
    }
}

void solve(int x, vector<pi>& C, vector<bool>& chk) {
    if(x < 0) return;
    chk[x] = true;
    solve(C[x].se, C, chk);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<pii> A(m);
    vector<int> B;
    vector<pi> C(n, {INF, -1}), D(n, {INF, -1});
    for(auto &i : A) {
        cin >> i.fi >> i.se.fi >> i.se.se;
        --i.fi;
        B.push_back(i.se.fi);
        B.push_back(i.se.se);
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    seg = vector<pi>(4*B.size(), {INF, -1});
    lazy = vector<pi>(4*B.size(), {INF, -1});
    for(auto &i : A) {
        i.se.fi = lower_bound(B.begin(), B.end(), i.se.fi)-B.begin();
        i.se.se = lower_bound(B.begin(), B.end(), i.se.se)-B.begin();
        i.se.se++;
    }
    for(int i = 0, j = 0, k = 0; i < n; i++) {
        for(; A[k].fi <= i && k < m; k++) {
            pi tmp = query(1, 0, B.size(), A[k].se.fi, A[k].se.se);
            if(tmp.fi < INF) C[i] = merge(C[i], {tmp.fi+i-1, tmp.se});
        }
        if(C[i].fi == INF) C[i].fi = i;
        for(; A[j].fi <= i && j < m; j++) update(1, 0, B.size(), A[j].se.fi, A[j].se.se, {C[i].fi-i, i});
        if(i) {
            pi tmp = merge({C[i-1].fi, i-1}, D[i-1]);
            D[i] = {tmp.fi+1, tmp.se};
        } else D[i] = {1, -1};
    }
    pi ans = merge(C.back(), D.back());
    cout << ans.fi << "\n";
    vector<bool> chk(n, false);
    if(ans == C.back()) solve(n-1, C, chk);
    else solve(ans.se, C, chk);
    for(int i = 0; i < n; i++) {
        if(!chk[i]) cout << i+1 << " ";
    }
    if(ans.fi > 0) cout << "\n";
    return 0;
}