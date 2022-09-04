#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+5;
const int P = 1000000007;
const ll LLINF = (ll)1e18+5;

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
    for (auto i: arr) out << i << ' ';
    out << '\n';
    return out;
}

class segtree {
    private:
    int n;
    vector<int> seg;
    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    void update(int i, int s, int e, int j, int x) {
        if(s > j || e <= j) return;
        if(s+1 == e) seg[i] += x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(e <= l || r <= s) return 0;
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r) + query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    segtree(vector<int>& A) {
        this->n = A.size();
        seg.resize(4*n);
        init(1, 0, n, A);
    }
    void update(int j, int x) { update(1, 0, n, j, x); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, w; cin >> n >> w;
    vector<vector<pll>> D(w+1); //logs of time and sum of times
    vector<int> S(n, 0); //scores
    vector<ll> B(n, 0LL); //sum of ranks
    vector<pll> H(n, {1LL, -1LL}); //history of rank and time
    vector<int> seg_init(w+1, 0);
    seg_init[0] = n;
    segtree T(seg_init);
    for(ll i = 0LL; i < w; i++) {
        int k; cin >> k;
        vector<int> A(k);
        for(auto &j : A) { cin >> j; j--; }
        sort(A.begin(), A.end(), [&](int a, int b) {
            return S[a] > S[b];
        });
        for(auto c : A) {
            vector<pll>& TV = D[S[c]];
            int idx = upper_bound(TV.begin(), TV.end(), make_pair(H[c].se, LLINF)) - TV.begin();
            ll tmp = 0LL;
            if(TV.size()) tmp = TV.back().se;
            if(idx > 0) tmp -= TV[idx-1].se;
            B[c] += H[c].fi * (i - H[c].se) - tmp + i * ((int)TV.size() - idx);
        }
        for(auto c : A) {
            vector<pll>& TV = D[S[c]];
            pll tmp = {0LL, 0LL};
            if(TV.size()) tmp = TV.back();
            TV.push_back({i, tmp.se+i});
            T.update(S[c]++, -1);
            T.update(S[c], 1);
            H[c] = {T.query(S[c]+1, w+1)+1LL, i};
            //cout << "H[c].fi " << H[c].fi << "\n";
        }
    }
    for(int c = 0; c < n; c++) {
        vector<pll>& TV = D[S[c]];
        //cout << "S[c] : " << S[c] << " " << H[c].se << "\n";
        int idx = upper_bound(TV.begin(), TV.end(), make_pair(H[c].se, LLINF)) - TV.begin();
        //cout << "idx : " << idx << "\n";
        ll tmp = 0LL;
        if(TV.size()) tmp = TV.back().se;
        if(idx > 0) tmp -= TV[idx-1].se;
        //cout << H[c].fi << " " << w << " " << H[c].se << "\n";
        //cout << tmp << " " << TV.size() << " " << idx << "\n";
        //cout << c << " " << H[c].fi * (w - H[c].se) << " " << tmp << " " << w * ((int)TV.size() - idx) << "\n";
        //cout << B[c] << " " << H[c].fi * (w - H[c].se) - tmp + w * ((int)TV.size() - idx) << "\n";
        B[c] += H[c].fi * (w - H[c].se) - tmp + w * ((int)TV.size() - idx) - 1LL;
    }
    cout << fixed << setprecision(13);
    for(auto i : B) cout << (long double)i/w << "\n";
    return 0;
}