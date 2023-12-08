#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
#define fi first
#define se second
const ll LLINF = (ll)1e18+5;

class SegTree {
    private:
    int n;
    vector<ll> seg, lazy;
    void prop(int i, int s, int e) {
        if(s+1 != e) {
            seg[i<<1] += lazy[i];
            seg[i<<1|1] += lazy[i];
            lazy[i<<1] += lazy[i];
            lazy[i<<1|1] += lazy[i];
        }
        lazy[i] = 0LL;
    }
    ll query(int i, int s, int e, int l, int r) {
        prop(i, s, e);
        if(e <= l || r <= s) return LLINF;
        if(l <= s && e <= r) return seg[i];
        return min(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }
    void update(int i, int s, int e, int l, int r, ll x) {
        prop(i, s, e);
        if(e <= l || r <= s) return;
        if(l <= s && e <= r) {
            lazy[i] += x;
            seg[i] += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }

    public:
    SegTree(int n) {
        seg.resize(4*n, 0LL);
        lazy.resize(4*n, 0LL);
        this->n = n;
    }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
    void update(int l, int r, ll x) { update(1, 0, n, l, r, x); }
};

ll binsearch(int idx, vector<int> &st, vector<int> &A) {
    auto iter = lower_bound(st.begin(), st.end(), idx);
    if(iter == st.begin()) return LLINF;
    if(iter == st.end()) return 0LL;
    return A[*iter];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p; cin >> n >> p;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<int> st = {-1, 0};
    vector<ll> dp(n); dp[0] = A[0];
    SegTree S(n);
    int jb = -1;
    for(int i = 1; i < n; i++) {
        S.update(i-1, i, dp[i-1]-(i-1)+A[i]);
        while(st.size() > 1 && A[st.back()] <= A[i]) {
            int e = st.back();
            st.pop_back();
            int s = st.back();
            S.update(max(0, s), e, A[i]-A[e]);
        }
        st.push_back(i);
        dp[i] = LLINF;
        while(jb < i-1 && binsearch(jb+1, st, A)+i-jb-1 > p) jb++;
        dp[i] = S.query(max(0, jb), i)+i-1;
        if(jb < 0) dp[i] = min(dp[i], (long long)A[st[1]]+i);
    }
    cout << dp.back() << "\n";
    return 0;
}
