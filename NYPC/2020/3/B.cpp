#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef pair<pi, int> pii;
#define fi first
#define se second

vector<int> seg, C;

void update(int i, int s, int e, int j, int x) {
    if(s > j || e <= j) return;
    if(s+1 == e) seg[i] += x;
    else {
        update(i<<1, s, s+e>>1, j, x);
        update((i<<1)+1, s+e>>1, e, j, x);
        seg[i] = seg[i<<1]+seg[(i<<1)+1];
    }
}

int query(int i, int s, int e, int l, int r) {
    if(s >= r || l >= e) return 0;
    if(l <= s && e <= r) return seg[i];
    return query(i<<1, s, s+e>>1, l, r)+query((i<<1)+1, s+e>>1, e, l, r);
}

void solve(vector<pii>& A, vector<int>& L, vector<int>& R, int n) {
    for(int i = 0, l = 0; i < n; i++) {
        if(i == n-1 || A[i+1].fi.se > A[i].fi.se || A[i+1].fi.fi > 1+A[i].fi.fi) {
            for(int j = l; j <= i; j++) {
                L[A[j].se] = j-l;
                R[A[j].se] = i-j;
            }
            l = i+1;
        }
    }
}

void chk(vector<pii>& A, vector<int>& r, int n) {
    for(int i = 0, l = 0; i < n; i++) {
        if(i == n-1 || A[i+1].fi.se > A[i].fi.se || A[i+1].fi.fi > 1+A[i].fi.fi) {
            seg = vector<int>((i-l+1)*4, 0);
            //cout << seg.size() << endl;
            for(int j = l; j <= i; j++) {
                if(r[A[j].se] == 0) continue;
                //cout << j << " " << r[A[j].se] << endl;
                update(1, 0, i-l+1, j-r[A[j].se]-l, 1);
                if(j != i) update(1, 0, i-l+1, j+r[A[j].se]-l+1, -1);
            }
            //for(auto &j : seg) cout << j << " ";
            //cout << endl;
            for(int j = l; j <= i; j++) C[A[j].se] += query(1, 0, i-l+1, 0, j-l+1);
            //for(auto &j : seg) cout << j << " ";
            //cout << endl;
            l = i+1;
        }
    }
}

bool cmp(pii a, pii b) {
    if(a.fi.se == b.fi.se) return a.fi.fi < b.fi.fi;
    return a.fi.se < b.fi.se;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<pi> A(n);
    vector<pii> X(n), Y(n);
    vector<int> L(n), R(n), U(n), D(n), r(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    for(int i = 0; i < n; i++) {
        X[i].fi = A[i];
        Y[i].fi = {A[i].se, A[i].fi};
        X[i].se = Y[i].se = i;
    }
    sort(X.begin(), X.end(), cmp); solve(X, L, R, n);
    sort(Y.begin(), Y.end(), cmp); solve(Y, D, U, n);
    for(int i = 0; i < n; i++) r[i] = min(min(L[i], R[i]), min(D[i], U[i]));
    C.resize(n);
    chk(X, r, n); chk(Y, r, n);
    //for(auto &i : C) cout << i << " ";
    //cout << endl;
    if((*min_element(C.begin(), C.end())) > 0) {
        vector<pii> pts;
        for(int i = 0; i < n; i++)
            if(r[i] > 0) pts.push_back({A[i], r[i]});
        cout << pts.size() << "\n";
        for(auto &i : pts) cout << i.fi.fi << " " << i.fi.se << " " << i.se << "\n";
    } else cout << "-1\n";
    return 0;
}