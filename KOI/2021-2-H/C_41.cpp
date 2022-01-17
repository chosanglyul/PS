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

vector<int> getpi(string& b) {
    vector<int> pi(b.size(), 0);
    for(int i = 1; i < b.size(); i++) {
        pi[i] = pi[i-1];
        while(pi[i] > 0 && b[pi[i]] != b[i]) pi[i] = pi[pi[i]-1];
        if(b[pi[i]] == b[i]) pi[i]++;
    }
    return pi;
}

int kmp(string& a, string& b, vector<int>& pi) {
    int ans = 0, j = 0;
    for(int i = 0; i < a.size(); i++) {
        while(j > 0 && b[j] != a[i]) j = pi[j-1];
        if(b[j] == a[i]) j++;
        if(j == b.size()) return j;
        ans = max(ans, j);
    }
    return ans;
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
        vector<vector<int>> C(2*n+1), D(n);
        for(int i = 0; i < n; i++) {
            int tmp = A[i]+n;
            if(C[tmp].size()) {
                int mi = sa.query(C[tmp][0], i);
                if(mi == A[i]) {
                    for(auto j : C[tmp])
                        D[j].push_back(i-j);
                } else C[tmp].clear();
            }
            C[tmp].push_back(i);
        }
        /*
        for(auto &i : D) {
            for(auto j : i) cout << j << " ";
            cout << "\n";
        }
        */
        int ans = 0;
        for(int i = 0; i < a.size(); i++) {
            string tmp(a.begin()+i, a.end());
            vector<int> T = getpi(tmp);
            int k = kmp(b, tmp, T);
            auto iter = upper_bound(D[i].begin(), D[i].end(), k);
            if(iter == D[i].begin()) continue;
            ans = max(ans, *(--iter));
        }
        cout << ans << "\n";
    }
	return 0;
}
