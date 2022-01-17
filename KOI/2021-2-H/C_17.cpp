#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;
typedef pair<pil, ll> piil;
#define fi first
#define se second
const int INF = (int)1e9;

class segtree {
    private:
    int n;
    vector<int> seg;
    void init(int i, int s, int e, vector<int>& A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }
    int query(int i, int s, int e, int l, int r) {
        if(s >= r || l >= e) return INF;
        if(l <= s && e <= r) return seg[i];
        return min(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }
    public:
    segtree(vector<int>& A) {
        n = A.size();
        seg.resize(4*n);
        init(1, 0, n, A);
    }
    int query(int l, int r) { return query(1, 0, n, l, r); }
};

vector<int> stov(string& a) {
    vector<int> A(a.size()+1, 0);
    for(int i = 0; i < a.size(); i++) {
        A[i+1] = A[i];
        if(a[i] == '(') A[i+1]++;
        else A[i+1]--;
    }
    return A;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        string a, b; cin >> a >> b;
        vector<int> A = stov(a), B = stov(b);
        segtree sa(A), sb(B);
        int n = A.size();
        vector<int> C(2*n+1, -1);
        int ans = 0;
        for(int i = 0; i < n; i++) {
            int tmp = A[i]+n;
            if(C[tmp] == -1) C[tmp] = i;
            else {
                int mi = sa.query(C[tmp], i);
                if(mi == A[i]) ans = max(i-C[tmp], ans);
                else C[tmp] = i;
            }
        }
        cout << ans << "\n";
    }
	return 0;
}
